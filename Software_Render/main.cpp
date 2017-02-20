#include"engine.h"
#include"SoftRenderWindow.h"
#include<iostream>
int main()
{
	softRenderWindow win("render",800,600);
	win.show();
	bool exit = false;
	MSG msg;
	renderEngine render;
	framebuffer rt;
	Texture texture;
	texture.load("Nature.bmp");
	win.renderTarget(&rt);
	render.setRenderTarget(rt);
	while (!exit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				exit = true;
			else if (win.changeSize)
			{
				win.initBitmapEnv(win.width, win.height);
				InvalidateRect(win.getMyWindow(), NULL, FALSE);
				win.changeSize = false;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Sleep(1000);
			render.drawTriangle(glm::vec2(-0.5,-0.5), glm::vec2(0.5, -0.5),glm::vec2(0.5, 0.5),glm::vec2(0.0,0.0),glm::vec2(1.0,0.0),glm::vec2(1.0,1.0),&texture);
			win.swapBuffer();
		}
	}
	return 0;
}