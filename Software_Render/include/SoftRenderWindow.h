#pragma once
#include"myWindow.h"
#include"framebuffer.h"
#include"engine.h"

class softRenderWindow : public myWindow
{
public:
	softRenderWindow(const char* WindowName, int Width, int height);
	~softRenderWindow();
	void initBitmapEnv(int width,int height);
	void swapBuffer();
	void bindEngine(renderEngine* engine);
	void clear();
private:
	HDC screenHDC, bitmapHDC;
	HBITMAP frontbuffer_handle;
	HBITMAP backbuffer_handle;
	unsigned char* frontbuffer_pixel;
	unsigned char* backbuffer_pixel;
	unsigned char* pixels;
	bool front;
	framebuffer renderTarget;
};