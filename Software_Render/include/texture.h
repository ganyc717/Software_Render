#pragma once
#include"glm\glm.hpp"

class Texture
{
public:
	~Texture();
	bool load(const char* FileName);
	int width;
	int height;
	unsigned char* data;
};

class sampler
{
public:
	static glm::ivec3 texture2D(Texture* texture,float u, float v);
	static glm::ivec3 texture2D(Texture* texture, glm::vec2 uv);
};