#pragma once
#include"framebuffer.h"
#include"primitive.h"
#include"texture.h"


class renderEngine
{
public:
//	void drawLine(glm::vec2 x1, glm::vec2 x2);
//	void drawTriangle(glm::vec2 x1, glm::vec2 x2, glm::vec2);
	void drawTriangle(glm::vec4 x1, glm::vec4 x2, glm::vec4, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, Texture* texture);
	void drawPrimitive(Primitive primitive, Texture* texture);
	void setRenderTarget(framebuffer* RT);
private:
//	void drawLine(glm::ivec2 x1, glm::ivec2 x2);
//	void drawFlatTriangle(glm::vec3 x1, glm::vec3 x2, glm::vec3 x3);
//	void drawFlatTriangle(glm::ivec2 p1, glm::ivec2 p2, glm::ivec2 p3);
//	void drawFlatTriangle(glm::vec4, glm::vec4, glm::vec4, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3,Texture* texture);
	void drawFlatTriangle(glm::ivec2 p1, glm::ivec2 p2, glm::ivec2 p3,float depth1,float depth2,float depth3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3,Texture* texture);

	glm::ivec2 mapPoint(glm::vec2 point);
	framebuffer* rendertarget;
};