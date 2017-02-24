#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"engine.h"
#include"SoftRenderWindow.h"
#include<iostream>
#include"pipeline.h"
int main()
{
	softRenderWindow win("render",800,600);
	win.show();
	bool exit = false;
	MSG msg;
	renderEngine engine;
	framebuffer rt;
	Texture texture;
	Pipeline pipeline;
	texture.load("texture\\Nature.bmp");
	win.bindEngine(&engine);
	glm::mat4 M = glm::mat4(1.0);

	glm::mat4 P = glm::perspective(glm::radians(60.0f), (float)win.width / (float)win.height, (float)0.1, (float)500.0);

	pipeline.engine = &engine;
	pipeline.texture = &texture;
	float vertex[] = {
		-1.0,-1.0,0.0,
		1.0,-1.0,0.0,
		1.0,1.0,0.0,
		1.0,1.0,0.0,
		-1.0,1.0,0.0,
		-1.0,-1.0,0.0
	};
	float uv[] = {
		0.0,0.0,
		1.0,0.0,
		1.0,1.0,
		1.0,1.0,
		0.0,1.0,
		0.0,0.0
	};
	pipeline.LoadVertex(vertex);
	pipeline.LoadTexCoord(uv);
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

			win.clear();
			glm::mat4 V = win.getCamera()->getViewMatrix();
			glm::mat4 MVP = P*V*M;
			pipeline.setMVPMat(MVP);
			/*
			engine.drawTriangle(glm::vec2(-0.5,-0.5), glm::vec2(0.5, -0.5),glm::vec2(0.5, 0.5),glm::vec2(0.0,0.0),glm::vec2(2.0,0.0),glm::vec2(2.0,2.0),&texture);
			engine.drawTriangle(glm::vec2(0.5, 0.5), glm::vec2(-0.5, 0.5), glm::vec2(-0.5, -0.5), glm::vec2(2.0, 2.0), glm::vec2(0.0, 2.0), glm::vec2(0.0, 0.0), &texture);
			*/
			pipeline.runPipeline(2);
			win.swapBuffer();
		}
	}
	return 0;
}