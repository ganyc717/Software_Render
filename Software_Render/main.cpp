#include"engine.h"
#include"SoftRenderWindow.h"
#include<iostream>
int main()
{
	softRenderWindow win("render",800,600);
	win.show();
	bool exit = false;
	MSG msg;
	renderEngine engine;
	framebuffer rt;
	Texture texture;
	texture.load("texture\\Nature.bmp");
	win.bindEngine(&engine);
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
			engine.drawTriangle(glm::vec2(-0.5,-0.5), glm::vec2(0.5, -0.5),glm::vec2(0.5, 0.5),glm::vec2(0.0,0.0),glm::vec2(2.0,0.0),glm::vec2(2.0,2.0),&texture);
			engine.drawTriangle(glm::vec2(0.5, 0.5), glm::vec2(-0.5, 0.5), glm::vec2(-0.5, -0.5), glm::vec2(2.0, 2.0), glm::vec2(0.0, 2.0), glm::vec2(0.0, 0.0), &texture);
			win.swapBuffer();
		}
	}
	return 0;
}