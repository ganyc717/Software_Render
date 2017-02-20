#include"texture.h"
#include <iostream>  
#include <fstream>  
#include <cstdlib>

Texture::~Texture()
{
	if (data != NULL)
		delete[] data;
}

bool Texture::load(const char* name)
{
	std::ifstream fp;
	fp.open(name,std::ios::binary);
	if (!fp.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return false;
	}
	long start, end;
	uint32_t offset;
	fp.seekg(0, std::ios::beg);
	start = fp.tellg();
	fp.seekg(0, std::ios::end);
	end = fp.tellg();
	long size = end - start;
	fp.seekg(10, std::ios::beg);
	fp.read((char*)&offset, 4);

	fp.seekg(18, std::ios::beg);
	fp.read((char*)&width, 4);

	fp.seekg(22, std::ios::beg);
	fp.read((char*)&height, 4);

	fp.seekg(offset, std::ios::beg);
	data = new unsigned char[width * height * 3];
	unsigned char* pointer = data;
	for (int i = 0; i < height; i++)
	{
		fp.read((char*)pointer, width * 3);
		pointer += width * 3;
		int align = (width * 3 + 3) / 4 * 4 - width * 3;
		fp.seekg(align, std::ios::cur);
	}
	return true;
}

glm::ivec3 sampler::texture2D(Texture* texture, glm::vec2 uv)
{
	return sampler::texture2D(texture, uv.x, uv.y);
}


#define PIXEL_R(u,v) texture->data[v * texture->width * 3 + u * 3 + 2]
#define PIXEL_G(u,v) texture->data[v * texture->width * 3 + u * 3 + 1]
#define PIXEL_B(u,v) texture->data[v * texture->width * 3 + u * 3 ]

#define PIXEL(u,v) glm::vec3(PIXEL_R(u,v),PIXEL_G(u,v),PIXEL_B(u,v))


glm::ivec3 sampler::texture2D(Texture* texture, float U, float V)
{
	U = glm::abs(U);
	V = glm::abs(V);
	int u_floor = glm::floor(U) / 2 * 2;
	int v_floor = glm::floor(V) / 2 * 2;
	float u = U - u_floor;
	float v = V - v_floor;
	if (u >= 1.0)
		u = 2.0 - u;
	if (v >= 1.0)
		v = 2.0 - v;

	int u_pos = glm::floor(u / (1.0 / texture->width));
	int v_pos = glm::floor(v / (1.0 / texture->height));
	int u_pos_next = u_pos + 1;
	int v_pos_next = v_pos + 1;

	
	if (u_pos == texture->width)
		u_pos == texture->width - 1;
	if (v_pos == texture->height)
		v_pos = texture->height - 1;

	if(u_pos == texture->width - 1)
		u_pos_next = u_pos - 1;
	if (v_pos == texture->height - 1)
		v_pos_next = v_pos - 1;
	float u_weight = 1.0 - (u - (float)u_pos / texture->width);
	float v_weight = 1.0 - (v - (float)v_pos / texture->height);
	glm::vec3 UV = PIXEL(u_pos, v_pos);
	glm::vec3 UNext_V = PIXEL(u_pos_next, v_pos);
	glm::vec3 U_VNext = PIXEL(u_pos, v_pos_next);
	glm::vec3 UNext_VNext = PIXEL(u_pos_next, v_pos_next);
	glm::vec3 color = u_weight * v_weight * UV +
		u_weight * (1 - v_weight) * U_VNext +
		(1 - u_weight) * v_weight * UNext_V +
		(1 - u_weight) * (1 - v_weight) * UNext_VNext;
	return glm::ivec3(glm::floor(color.x), glm::floor(color.y), glm::floor(color.z));
}