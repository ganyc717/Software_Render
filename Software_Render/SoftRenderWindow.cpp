#include"SoftRenderWindow.h"

void softRenderWindow::renderTarget(framebuffer* frame)
{
	frame->width = width;
	frame->height = height;
	if (front)
	{
		frame->pixels = backbuffer_pixel;
	}
	else
	{
		frame->pixels = frontbuffer_pixel;
	}
}

void softRenderWindow::clear()
{
	for (int i = 0; i < 24 / 8 * width*height ; i++)
		frontbuffer_pixel[i] = 0xf0;
	for (int i = 0 ; i < 24 / 8 * width*height; i++)
		backbuffer_pixel[i] = 0xf0;
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
	frontbuffer_handle = CreateDIBSection(NULL, &bitmapInfo, DIB_RGB_COLORS, (void**)&frontbuffer_pixel, NULL, 0);
	backbuffer_handle = CreateDIBSection(NULL, &bitmapInfo, DIB_RGB_COLORS, (void**)&backbuffer_pixel, NULL, 0);
	for (int i = 0; i < bitmapInfo.bmiHeader.biBitCount / 8 * width*height ; i++)
		frontbuffer_pixel[i] = 0x00;
	for (int i = 0 ; i < bitmapInfo.bmiHeader.biBitCount / 8 * width*height; i++)
		backbuffer_pixel[i] = 0x00;
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

}

softRenderWindow::~softRenderWindow()
{
	DeleteObject(frontbuffer_handle);
	DeleteObject(backbuffer_handle);
	DeleteDC(bitmapHDC);
	ReleaseDC(getMyWindow(), screenHDC);
}


void softRenderWindow::swapBuffer()
{
	if (front)
	{
		SelectObject(bitmapHDC, backbuffer_handle);
	}
	else
	{
		SelectObject(bitmapHDC, frontbuffer_handle);
	}
	front = !front;
	BitBlt(screenHDC, 0, 0, width, height, bitmapHDC, 0, 0, SRCCOPY);
}