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
/*
void renderEngine::drawLine(glm::ivec2 p1, glm::ivec2 p2)
{
	if (p1.x == p2.x)
	{
		for (int y = glm::min(p1.y, p2.y); y <= glm::max(p1.y, p2.y); y++)
		{
			COLOR_RED(p1.x, y);
		}
		return;
	}
	if (p1.y == p2.y)
	{
		for (int x = glm::min(p1.x, p2.x); x <= glm::max(p1.x, p2.x); x++)
		{
			COLOR_RED(x, p1.y);
		}
		return;
	}
	float k = (float)(p1.y - p2.y) / (p1.x - p2.x);
	float b = p1.y - k * p1.x;
	float delta = k * glm::min(p1.x, p2.x) + b;
	if (glm::abs(k) <= 1)
	{
		for (int x = glm::min(p1.x, p2.x); x <= glm::max(p1.x, p2.x); x++)
		{
			int y = glm::floor(delta);
			COLOR_RED(x, y);
			delta += k;
		}
	}
	else
	{
		k = 1 / k;
		b = -b / k;
		float delta = k * glm::min(p1.y, p2.y) + b;
		for (int y = glm::min(p1.y, p2.y); y <= glm::max(p1.y, p2.y); y++)
		{
			int x = glm::floor(delta);
			COLOR_RED(x, y);
			delta += k;
		}
	}
}
*/
/*
void renderEngine::drawLine(glm::vec2 x1, glm::vec2 x2)
{
	glm::ivec2 p1, p2;
	p1 = mapPoint(x1);
	p2 = mapPoint(x2);
	drawLine(p1, p2);
}
*/
/*
void renderEngine::drawFlatTriangle(glm::ivec2 p1, glm::ivec2 p2, glm::ivec2 p3)
{
	assert(p2.y == p3.y);
	float m1 = (float)(p1.x - p2.x) / (p1.y - p2.y);
	float m2 = (float)(p1.x - p3.x) / (p1.y - p3.y);
	float b1 = (float)p1.x - m1 * p1.y;
	float b2 = (float)p1.x - m2 * p1.y;
	float delta_Line1 = m1 * p1.y + b1;
	float delta_Line2 = m2 * p1.y + b2;

	int direction_Y = p1.y <= p2.y ? 1 : -1;
	m1 *= direction_Y;
	m2 *= direction_Y;

	for (int i = 0; i <= glm::abs(p2.y - p1.y); i++)
	{
		int y = p1.y + direction_Y * i;
		int edge1 = glm::floor(delta_Line1);
		int edge2 = glm::floor(delta_Line2);
		int direction_X = edge1 <= edge2 ? 1 : -1;

		for (int j = 0; j <= glm::abs(edge1 - edge2); j++)
		{
			int x = edge1 + direction_X * j;
			COLOR_RED(x, y);
		}
		delta_Line1 += m1;
		delta_Line2 += m2;
	}

}
void renderEngine::drawFlatTriangle(glm::vec3 x1, glm::vec3 x2, glm::vec3 x3)
{
	glm::ivec2 p1, p2, p3;
	p1 = mapPoint(x1);
	p2 = mapPoint(x2);
	p3 = mapPoint(x3);
	drawFlatTriangle(x1, x2, x3);
}

void renderEngine::drawTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2 x3)
{
	glm::ivec2 p1, p2, p3, exchange;
	p1 = mapPoint(x1);
	p2 = mapPoint(x2);
	p3 = mapPoint(x3);
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
				//	p1.y>=p3.y>=p2.y
			}
			else
			{
				EXCHANGE(p1, p3, exchange);
				EXCHANGE(p2, p3, exchange);
				//	p3.y>=p1.y>=p2.y
			}
		}
	}
	else
	{
		if (p3.y >= p2.y)
		{
			EXCHANGE(p1, p3, exchange);
			//	p3.y>=p2.y>=p1.y
		}
		else
		{
			if (p3.y >= p1.y)
			{
				EXCHANGE(p1, p2, exchange);
				EXCHANGE(p2, p3, exchange);
				//	p2.y>=p3.y>=p1.y
			}
			else
			{
				EXCHANGE(p1, p2, exchange);
				//	p2.y>=p1.y>=p3.y
			}
		}
	}
	if ((p1.y - p2.y) * (p1.x - p3.x) == (p1.y - p3.y) * (p1.x - p2.x))  //collinear
	{
		drawLine(p1, p3);
		return;
	}
	if ((p2.y == p1.y))  //flat triangle
	{
		drawFlatTriangle(p3, p1, p2);
		return;
	}
	if ((p2.y == p3.y))    //flat triangle
	{
		drawFlatTriangle(p1, p2, p3);
		return;
	}

	float k = (float)(p1.y - p3.y) / (p1.x - p3.x);
	float b = p1.y - k * p1.x;
	glm::ivec2 p4 = glm::ivec2(glm::floor((p2.y - b) / k), p2.y);
	drawFlatTriangle(p1, p2, p4);
	drawFlatTriangle(p3, p2, p4);
}

void renderEngine::drawFlatTriangle(glm::vec4 x1, glm::vec4 x2, glm::vec4 x3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, Texture* texture)
{
	glm::ivec2 p1, p2, p3, exchange;
	p1 = mapPoint(x1);
	p2 = mapPoint(x2);
	p3 = mapPoint(x3);
	drawFlatTriangle(p1, p2, p3,x1.z,x2.z,x3.z, uv1, uv2, uv3, texture);
}
*/
void renderEngine::drawFlatTriangle(glm::ivec2 p1, glm::ivec2 p2, glm::ivec2 p3,float depth1,float depth2,float depth3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3,Texture* texture)
{
	assert(p2.y == p3.y);
	float m1 = (float)(p1.x - p2.x) / (p1.y - p2.y);
	float m2 = (float)(p1.x - p3.x) / (p1.y - p3.y);
	float b1 = (float)p1.x - m1 * p1.y;
	float b2 = (float)p1.x - m2 * p1.y;
	float delta_Line1 = m1 * p1.y + b1;
	float delta_Line2 = m2 * p1.y + b2;
	glm::vec2 alpha = uv2 - uv1;
	glm::vec2 beta = uv3 - uv2;
	float alpha_depth = depth2 - depth1;
	float beta_depth = depth3 - depth2;
	float v_step = 1.0 / (float)(glm::abs(p1.y - p2.y));
	float u_step = 1.0 / (float)(glm::abs(p1.x - p2.x));
	glm::vec2 UV = uv1;
	float depth = depth1;
	int direction_Y = p1.y <= p2.y ? 1 : -1;
	m1 *= direction_Y;
	m2 *= direction_Y;

	for (int i = 0; i <= glm::abs(p2.y - p1.y); i++)
	{
		int y = p1.y + direction_Y * i;
		int edge1 = glm::floor(delta_Line1);
		int edge2 = glm::floor(delta_Line2);
		int direction_X = edge1 <= edge2 ? 1 : -1;
		glm::vec2 scan = UV;
		float scan_depth = depth;
		for (int j = 0; j <= glm::abs(edge1 - edge2); j++)
		{
			int x = edge1 + direction_X * j;
			if (DEPTH(x, y) > scan_depth)
			{
				COLOR(x, y, sampler::texture2D(texture, scan));
				DEPTH(x, y) = scan_depth;
			}
			//COLOR(x, y, sampler::texture2D(texture, scan));
			scan += u_step * beta;
			scan_depth += u_step * beta_depth;
		}
		delta_Line1 += m1;
		delta_Line2 += m2;
		UV += v_step * alpha;
		depth += v_step * alpha_depth;
	}
}

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
		drawFlatTriangle(point3, point1, point2, p3.z, p1.z, p2.z, UV3, UV1, UV2, texture);
		return;
	}
	if ((point2.y == point3.y))    //flat triangle
	{
		drawFlatTriangle(point1, point2, point3, p1.z, p2.z, p3.z, UV1, UV2, UV3, texture);
		return;
	}

	float k = (float)(p1.y - p3.y) / (p1.x - p3.x);
	float b = p1.y - k * p1.x;
	glm::ivec2 point4 = glm::ivec2(glm::floor((p2.y - b) / k), p2.y);
	float delta = (float)(p1.y - p2.y) / (float)(p1.y - p3.y);
	glm::vec2 uv4 = UV1 + delta * (UV3 - UV1);
	float depth = p1.z + delta * (p3.z - p1.z);
	drawFlatTriangle(point1, point2, point4, p1.z, p2.z, depth, uv1, uv2, uv4, texture);
	drawFlatTriangle(point3, point2, point4, p3.z, p2.z, depth, uv3, uv2, uv4, texture);
}

void renderEngine::drawPrimitive(Primitive primitive, Texture* texture)
{
	drawTriangle(primitive.p1, primitive.p2, primitive.p3, primitive.uv1, primitive.uv2, primitive.uv3, texture);
}