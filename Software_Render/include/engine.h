#pragma once
#include"framebuffer.h"
#include"primitive.h"
#include"texture.h"


class renderEngine
{
public:
	void drawTriangle(glm::vec4 x1, glm::vec4 x2, glm::vec4, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, Texture* texture);
	void drawPrimitive(Primitive primitive, Texture* texture);
	void setRenderTarget(framebuffer* RT);
private:
	void drawFlatTriangle(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, Texture* texture);
	glm::ivec2 mapPoint(glm::vec2 point);
	framebuffer* rendertarget;
};