#include"engine.h"


#define BPP 3
#define PIXEL_R(x,y) (rendertarget->pixels[y * WIDTH * BPP + x * BPP + 2])
#define PIXEL_G(x,y) (rendertarget->pixels[y * WIDTH * BPP + x * BPP + 1])
#define PIXEL_B(x,y) (rendertarget->pixels[y * WIDTH * BPP + x * BPP ])

#define WIDTH  rendertarget->width
#define HEIGHT rendertarget->height
#define DEPTH(x,y) (rendertarget->depth[y * WIDTH + x])

#define COLOR_RED(x,y) 			PIXEL_R(x, y) = 0xff;\
								PIXEL_G(x, y) = 0x00;\
								PIXEL_B(x, y) = 0x00

#define COLOR(x,y,color)        PIXEL_R(x, y) = color.x;\
                                PIXEL_G(x, y) = color.y;\
                                PIXEL_B(x, y) = color.z

#define EXCHANGE(x,y,exchange)	exchange = x;\
								x = y;\
								y = exchange


glm::ivec2 renderEngine::mapPoint(glm::vec2 point)
{
	glm::ivec2 pixel_coordinate = glm::ivec2(glm::floor((point.x + 1.0) * WIDTH / 2), glm::floor((point.y + 1.0) * HEIGHT / 2));
	if (pixel_coordinate.x == WIDTH)
		pixel_coordinate.x = WIDTH - 1;
	if (pixel_coordinate.y == HEIGHT)
		pixel_coordinate.y = HEIGHT - 1;
	return pixel_coordinate;
}

void renderEngine::setRenderTarget(framebuffer* rt)
{
	rendertarget = rt;
}


void renderEngine::drawFlatTriangle(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, Texture* texture)
{
	glm::ivec2 point1, point2, point3;
	point1 = mapPoint(p1);
	point2 = mapPoint(p2);
	point3 = mapPoint(p3);
	float m1 = (float)(point1.x - point2.x) / (point1.y - point2.y);
	float m2 = (float)(point1.x - point3.x) / (point1.y - point3.y);
	float b1 = (float)point1.x - m1 * point1.y;
	float b2 = (float)point1.x - m2 * point1.y;

	float Line1 = m1 * point1.y + b1;
	float Line2 = m2 * point1.y + b2;
	glm::vec2 UV_alpha = uv2 - uv1;
	glm::vec2 UV_beta = uv3 - uv2;
	float W_alpha = p2.w - p1.w;
	float W_beta = p3.w - p2.w;

	float y_step = 1.0 / (float)(glm::abs(point1.y - point2.y));
	float x_step = 1.0 / (float)(glm::abs(point3.x - point2.x));
	glm::vec2 UV = uv1;
	float W = p1.w;
	int direction_Y = point1.y <= point2.y ? 1 : -1;
	m1 *= direction_Y;
	m2 *= direction_Y;

	for (int i = 0; i <= glm::abs(point2.y - point1.y); i++)
	{
		int y = point1.y + direction_Y * i;
		int edge1 = glm::floor(Line1);
		int edge2 = glm::floor(Line2);
		int direction_X = edge1 <= edge2 ? 1 : -1;
		glm::vec2 uv_scan = UV;
		float w_scan = W;
		for (int j = 0; j <= glm::abs(edge1 - edge2); j++)
		{
			int x = edge1 + direction_X * j;
			float w = 1 / w_scan;
			glm::vec2 uv = uv_scan * w;//  uv * w to recover its real value   (W == 1/w)
			if (DEPTH(x, y) > w)
			{
				COLOR(x, y, sampler::texture2D(texture, uv));
				DEPTH(x, y) = w;
			}
			uv_scan += x_step * UV_beta;
			w_scan += x_step * W_beta;
		}
		Line1 += m1;
		Line2 += m2;
		UV += y_step * UV_alpha;
		W += y_step * W_alpha;
	}
};
void renderEngine::drawTriangle(glm::vec4 x1, glm::vec4 x2, glm::vec4 x3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, Texture* texture)
{
	glm::vec2 UV1, UV2, UV3, exchangeUV;
	glm::vec4 p1, p2, p3, exchange;
	p1 = x1;
	p2 = x2;
	p3 = x3;

	UV1 = uv1;
	UV2 = uv2;
	UV3 = uv3;
	// First I want to sort the 3 points.
	if (p1.y >= p2.y)
	{
		if (p2.y >= p3.y)
		{
			//    p1.y>=p2.y>=p3.y
		}
		else
		{
			if (p1.y >= p3.y)
			{
				EXCHANGE(p2, p3, exchange);
				EXCHANGE(UV2, UV3, exchangeUV);
				//	p1.y>=p3.y>=p2.y
			}
			else
			{
				EXCHANGE(p1, p3, exchange);
				EXCHANGE(p2, p3, exchange);

				EXCHANGE(UV1, UV3, exchangeUV);
				EXCHANGE(UV2, UV3, exchangeUV);
				//	p3.y>=p1.y>=p2.y
			}
		}
	}
	else
	{
		if (p3.y >= p2.y)
		{
			EXCHANGE(p1, p3, exchange);
			EXCHANGE(UV1, UV3, exchangeUV);
			//	p3.y>=p2.y>=p1.y
		}
		else
		{
			if (p3.y >= p1.y)
			{
				EXCHANGE(p1, p2, exchange);
				EXCHANGE(p2, p3, exchange);

				EXCHANGE(UV1, UV2, exchangeUV);
				EXCHANGE(UV2, UV3, exchangeUV);
				//	p2.y>=p3.y>=p1.y
			}
			else
			{
				EXCHANGE(p1, p2, exchange);
				EXCHANGE(UV1, UV2, exchangeUV);
				//	p2.y>=p1.y>=p3.y
			}
		}
	}
	glm::ivec2 point1, point2, point3;
	point1 = mapPoint(p1);
	point2 = mapPoint(p2);
	point3 = mapPoint(p3);
	if ((point1.y - point2.y) * (point1.x - point3.x) == (point1.y - point3.y) * (point1.x - point2.x))  //collinear
	{
//		drawLine(p1, p3);
		return;
	}
	if ((point2.y == point1.y))  //flat triangle
	{
		drawFlatTriangle(p3, p1, p2, UV3, UV1, UV2, texture);
		return;
	}
	if ((point2.y == point3.y))    //flat triangle
	{
		drawFlatTriangle(p1, p2, p3, UV1, UV2, UV3, texture);
		return;
	}

	glm::vec4 p4;
	glm::vec2 UV4;
	float lambda = (p2.y - p1.y) / (p3.y - p1.y);
	p4 = lambda * (p3 - p1) + p1;
	UV4 = lambda * (UV3 - UV1) + UV1;
	drawFlatTriangle(p1, p2, p4, UV1, UV2, UV4, texture);
	drawFlatTriangle(p3, p2, p4, UV3, UV2, UV4, texture);
}

void renderEngine::drawPrimitive(Primitive primitive, Texture* texture)
{
	drawTriangle(primitive.position[0], primitive.position[1], primitive.position[2], primitive.uv[0], primitive.uv[1], primitive.uv[2], texture);
}