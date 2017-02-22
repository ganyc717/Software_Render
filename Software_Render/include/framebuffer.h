#pragma once
struct framebuffer
{
public:
	int width;
	int height;
	int bpp;
	unsigned char* pixels;
	float* depth;
};

