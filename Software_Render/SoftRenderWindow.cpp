#include"SoftRenderWindow.h"

void softRenderWindow::bindEngine(renderEngine* Engine)
{
	engine = Engine;
	engine->setRenderTarget(renderTarget);
}

void softRenderWindow::clear()
{
	for (int i = 0; i < 24 / 8 * width*height ; i++)
		frontbuffer.pixels[i] = 0xff;
	for (int i = 0 ; i < 24 / 8 * width*height; i++)
		backbuffer.pixels[i] = 0xf0;
}


void softRenderWindow::initBitmapEnv(int w, int h)
{
	BITMAPINFO bitmapInfo = { 0 };
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = w;
	bitmapInfo.bmiHeader.biHeight = h;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 24;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	if(frontbuffer_handle)
		DeleteObject(frontbuffer_handle);
	if(backbuffer_handle)
		DeleteObject(backbuffer_handle);
	frontbuffer_handle = CreateDIBSection(NULL, &bitmapInfo, DIB_RGB_COLORS, (void**)&frontbuffer.pixels, NULL, 0);
	backbuffer_handle = CreateDIBSection(NULL, &bitmapInfo, DIB_RGB_COLORS, (void**)&backbuffer.pixels, NULL, 0);
	frontbuffer.width = w;
	backbuffer.width = w;
	frontbuffer.height = h;
	backbuffer.height = h;
	frontbuffer.depth = new unsigned short[w * h];
	backbuffer.depth = new unsigned short[w * h];
	for (int i = 0; i < bitmapInfo.bmiHeader.biBitCount / 8 * width*height ; i++)
		frontbuffer.pixels[i] = 0x00;
	for (int i = 0 ; i < bitmapInfo.bmiHeader.biBitCount / 8 * width*height; i++)
		backbuffer.pixels[i] = 0x00;
	for (int i = 0; i < w * h; i++)
	{
		frontbuffer.depth[i] = 0xffff;
		backbuffer.depth[i] = 0xffff;
	}
}

softRenderWindow::softRenderWindow(const char* WindowName, int Width, int Height):myWindow(WindowName, Width, Height)
{
	screenHDC = GetDC(getMyWindow());
	bitmapHDC = CreateCompatibleDC(screenHDC);
	setPrivateData((long)this);
	frontbuffer_handle = NULL;
	backbuffer_handle = NULL;

	initBitmapEnv(width, height);
	SelectObject(bitmapHDC, frontbuffer_handle);
	front = true;
	renderTarget = &backbuffer;
}

softRenderWindow::~softRenderWindow()
{
	DeleteObject(frontbuffer_handle);
	DeleteObject(backbuffer_handle);
	DeleteDC(bitmapHDC);
	ReleaseDC(getMyWindow(), screenHDC);
	if (frontbuffer.depth)
		delete[] frontbuffer.depth;
	if (backbuffer.depth)
		delete[] backbuffer.depth;
}


void softRenderWindow::swapBuffer()
{
	if (front)
	{
		SelectObject(bitmapHDC, backbuffer_handle);
		renderTarget = &frontbuffer;
		engine->setRenderTarget(renderTarget);
	}
	else
	{
		SelectObject(bitmapHDC, frontbuffer_handle);
		renderTarget = &backbuffer;
		engine->setRenderTarget(renderTarget);
	}
	front = !front;
	BitBlt(screenHDC, 0, 0, width, height, bitmapHDC, 0, 0, SRCCOPY);
}