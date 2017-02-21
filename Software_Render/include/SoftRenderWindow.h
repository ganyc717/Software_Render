#pragma once
#include"myWindow.h"
#include"framebuffer.h"
#include"engine.h"
#include<memory>

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
	framebuffer frontbuffer;
	framebuffer backbuffer;
	bool front;
	framebuffer* renderTarget;
	renderEngine* engine;
};