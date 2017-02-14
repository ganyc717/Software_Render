#pragma once
#include"myWindow.h"

class softRenderWindow : public myWindow
{
public:
	softRenderWindow(const char* WindowName, int Width, int height);
	~softRenderWindow();
	void initBitmapEnv(int width,int height);
	void swapBuffer();
private:
	HDC screenHDC, bitmapHDC;
	HBITMAP frontbuffer_handle;
	HBITMAP backbuffer_handle;
	unsigned char* frontbuffer_pixel;
	unsigned char* backbuffer_pixel;
	bool front;
};