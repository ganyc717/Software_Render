#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"engine.h"
#include"SoftRenderWindow.h"
#include<iostream>
#include"pipeline.h"
#include"shape.h"
int main()
{
	softRenderWindow win("render",800,600);
	win.show();
	bool exit = false;
	MSG msg;
	renderEngine engine;
	framebuffer rt;
	Texture texture_grass,texture_box,texture_sky;
	Pipeline pipeline;
	texture_grass.load("texture\\grass.bmp");
	texture_box.load("texture\\box.bmp");
	texture_sky.load("texture\\sky.bmp");
	win.bindEngine(&engine);
	glm::mat4 M = glm::mat4(1.0);

	glm::mat4 P = glm::perspective(glm::radians(60.0f), (float)win.width / (float)win.height, (float)0.1, (float)500.0);

	pipeline.engine = &engine;
	
	const float unit_L = 10.0;
	
	float vertex[] = {
		-unit_L,0.0,unit_L,
		unit_L,0.0,unit_L,
		unit_L,0.0,-unit_L,

		unit_L,0.0,-unit_L,
		-unit_L,0.0,-unit_L,
		-unit_L,0.0,unit_L
	};

	float uv[] = {
		0.0,1.0,
		1.0,1.0,
		1.0,0.0,

		1.0,0.0,
		0.0,0.0,
		0.0,1.0
	};
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
			pipeline.LoadVertex(vertex);
			pipeline.LoadTexCoord(uv);
			pipeline.texture = &texture_grass;
			glm::mat4 V = win.getCamera()->getViewMatrix();
			glm::mat4 MVP = P*V*M;
			pipeline.setMVPMat(MVP);
			pipeline.runPipeline(0,2);
			
			pipeline.texture = &texture_sky;
			glm::mat4 Model_sky = glm::mat4(1.0);
			Model_sky = glm::translate(Model_sky, glm::vec3(0.0, 2* unit_L, 0.0));// Up
			MVP = P*V*Model_sky;
			pipeline.setMVPMat(MVP);
			pipeline.runPipeline(0, 2);

			Model_sky = glm::mat4(1.0);
			Model_sky = glm::translate(Model_sky, glm::vec3(0.0, unit_L, unit_L));
			Model_sky = glm::rotate(Model_sky,(float)glm::radians(90.0), glm::vec3(1.0, 0.0, 0.0));// back
			MVP = P*V*Model_sky;
			pipeline.setMVPMat(MVP);
			pipeline.runPipeline(0, 2);

			Model_sky = glm::mat4(1.0);
			Model_sky = glm::translate(Model_sky, glm::vec3(0.0, unit_L, -unit_L));
			Model_sky = glm::rotate(Model_sky, (float)glm::radians(90.0), glm::vec3(1.0, 0.0, 0.0));// front
			MVP = P*V*Model_sky;
			pipeline.setMVPMat(MVP);
			pipeline.runPipeline(0, 2);

			Model_sky = glm::mat4(1.0);
			Model_sky = glm::translate(Model_sky, glm::vec3(-unit_L, unit_L, 0.0));
			Model_sky = glm::rotate(Model_sky, (float)glm::radians(90.0), glm::vec3(0.0, 0.0, 1.0));// left
			MVP = P*V*Model_sky;
			pipeline.setMVPMat(MVP);
			pipeline.runPipeline(0, 2);

			Model_sky = glm::mat4(1.0);
			Model_sky = glm::translate(Model_sky, glm::vec3(unit_L, unit_L, 0.0));
			Model_sky = glm::rotate(Model_sky, (float)glm::radians(90.0), glm::vec3(0.0, 0.0, 1.0));// right
			MVP = P*V*Model_sky;
			pipeline.setMVPMat(MVP);
			pipeline.runPipeline(0, 2);
			
			pipeline.texture = &texture_box;
			pipeline.LoadVertex(cube_vertex);
			pipeline.LoadTexCoord(cube_texcoord);
			glm::mat4 Model_box = glm::mat4(1.0);
			Model_box = glm::translate(Model_box, glm::vec3(2.0, CubeL, -2.0));
			MVP = P*V*Model_box;
			pipeline.setMVPMat(MVP);
			pipeline.runPipeline(0, 12);

			Model_box = glm::translate(Model_box, glm::vec3(2*CubeL, 0.0, -CubeL));
			MVP = P*V*Model_box;
			pipeline.setMVPMat(MVP);
			pipeline.runPipeline(0, 12);

			win.swapBuffer();
		}
	}
	return 0;
}