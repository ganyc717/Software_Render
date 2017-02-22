#pragma once
#include"glm\glm.hpp"
#include"texture.h"
#include"engine.h"
#include<list>

class Pipeline
{
	void LoadVertex(float* );
	void LoadTexCoord(float* );
	void setMVPMat(glm::mat4 mvp);
	void runPipeline(int count);        //count is the triangle count we want to draw
	renderEngine* engine;
private:
	float* vertexIn;
	float* texcoord;
	void runVertexShader();
	void runClip();
	void runPerspectiveDivide();


	std::list<Primitive> primitive;
	glm::mat4 MVP;
};