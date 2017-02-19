#pragma once
#include"SoftRenderWindow.h"
#include"texture.h"

struct primitive
{
	glm::vec3 x1;
	glm::vec3 x2;
	glm::vec3 x3;
	glm::vec2 uv1;
	glm::vec2 uv2;
	glm::vec2 uv3;
};

class renderEngine
{
public:
	void drawLine(glm::vec2 x1, glm::vec2 x2);
	void drawTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2);
	void drawTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, Texture texture);
	void setRenderTarget(framebuffer RT);
private:
	void drawLine(glm::ivec2 x1, glm::ivec2 x2);
	void drawFlatTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2);
	void drawFlatTriangle(glm::ivec2 p1, glm::ivec2 p2, glm::ivec2 p3);
	void drawFlatTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3,Texture texture);
	void drawFlatTriangle(glm::ivec2 p1, glm::ivec2 p2, glm::ivec2 p3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3,Texture texture);

	glm::ivec2 mapPoint(glm::vec2 point);
	framebuffer rendertarget;
};