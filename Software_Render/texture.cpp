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

glm::ivec3 sampler::texture2D(Texture texture, float u, float v)
{
	int u_pos = glm::floor(u / (1.0 / texture.width));
	int v_pos = glm::floor(v / (1.0 / texture.height));
	int u_pos_next = u_pos + 1;
	int v_pos_next = v_pos + 1;
	
}