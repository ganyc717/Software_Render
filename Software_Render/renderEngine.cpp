#include"renderEngine.h"

#define BPP 3
#define PIXEL_R(x,y) (rendertarget.pixels[y * WIDTH * BPP + x * BPP + 2])
#define PIXEL_G(x,y) (rendertarget.pixels[y * WIDTH * BPP + x * BPP + 1])
#define PIXEL_B(x,y) (rendertarget.pixels[y * WIDTH * BPP + x * BPP ])

#define WIDTH  rendertarget.width 
#define HEIGHT rendertarget.height
#define COLOR_RED(x,y) 			PIXEL_R(x, y) = 0xff;\
								PIXEL_G(x, y) = 0x00;\
								PIXEL_B(x, y) = 0x00

glm::ivec2 renderEngine::mapPoint(glm::vec2 point)
{
	glm::ivec2 pixel_coordinate = glm::ivec2(glm::floor((point.x + 1.0) * WIDTH / 2), glm::floor((point.y + 1.0) * HEIGHT / 2));
	if (pixel_coordinate.x == WIDTH)
		pixel_coordinate.x = WIDTH - 1;
	if (pixel_coordinate.y == HEIGHT)
		pixel_coordinate.y = HEIGHT - 1;
	return pixel_coordinate;
}

void renderEngine::setRenderTarget(framebuffer rt)
{
	rendertarget.width = rt.width;
	rendertarget.height = rt.height;
	rendertarget.pixels= rt.pixels;
}

void renderEngine::drawLine(glm::vec2 x1, glm::vec2 x2)
{
	glm::ivec2 p1, p2;
	p1 = mapPoint(x1);
	p2 = mapPoint(x2);
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
	float delta = 0.0;
	if (glm::abs(k) <= 1)
	{
		for (int x = glm::min(p1.x, p2.x); x <= glm::max(p1.x, p2.x); x++)
		{
			int y = glm::floor(k * x + b);
			COLOR_RED(x, y);
		}
	}
	else
	{
		k = 1 / k;
		b = -b / k;
		float delta = 0.0;
		for (int y = glm::min(p1.y, p2.y); y <= glm::max(p1.y, p2.y); y++)
		{
			int x = glm::floor(k * y + b);
			COLOR_RED(x, y);
		}
	}
}


void renderEngine::drawFlatTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2 x3)
{
	glm::ivec2 p1, p2, p3;
	p1 = mapPoint(x1);
	p2 = mapPoint(x2);
	p3 = mapPoint(x3);

	assert(p2.y == p3.y);
	float m1 = (float)(p1.x - p2.x) / (p1.y - p2.y);
	float m2 = (float)(p1.x - p3.x) / (p1.y - p3.y);
	float b1 = (float)p1.x - m1 * p1.y;
	float b2 = (float)p1.x - m2 * p1.y;
	float delta_left = m1 * p1.y + b1;
	float delta_right = m2 * p1.y + b2;
	if (p1.y > p2.y)
	{
		for (int y = p1.y; y >= p2.y; y--)
		{
			int x1_left = glm::floor(delta_left);
			int x1_right = glm::floor(delta_right);
			for (int x = glm::min(x1_left, x1_right); x <= glm::max(x1_right, x1_left); x++) {
				COLOR_RED(x, y);
			}
			delta_left -= m1;
			delta_right -= m2;
		}
	}
	else
	{
		for (int y = p1.y; y <= p2.y; y++)
		{
			int x1_left = glm::floor(delta_left);
			int x1_right = glm::floor(delta_right);
			for (int x = glm::min(x1_left, x1_right); x <= glm::max(x1_right, x1_left); x++) {
				COLOR_RED(x, y);
			}
			delta_left += m1;
			delta_right += m2;
		}
	}
}

void renderEngine::drawTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2 x3)
{
}