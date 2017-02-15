#pragma once
#include"SoftRenderWindow.h"

class renderEngine
{
public:
	void drawLine(glm::vec2 x1, glm::vec2 x2);
	void drawFlatTriangle(glm::vec2 x1,glm::vec2 x2,glm::vec2);
	void drawTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2);
	void setRenderTarget(framebuffer RT);
private:
	glm::ivec2 mapPoint(glm::vec2 point);
	framebuffer rendertarget;
};