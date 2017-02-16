#include"renderEngine.h"
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
			render.drawTriangle(glm::vec2(0.3, -0.4), glm::vec2(0.5, -0.8),glm::vec2(0.1, -0.5));
			win.swapBuffer();
		}
	}
	return 0;
}