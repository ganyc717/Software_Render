#include"pipeline.h"

float Interpolation(float start, float end, float middle)
{
	assert(end != start);
	return (middle - start) / (end - start);
}

glm::vec4 Interpolation(glm::vec4 start, glm::vec4 end, float k)
{
	return k * (end - start) + start;
}
glm::vec2 Interpolation(glm::vec2 start, glm::vec2 end, float k)
{
	return k * (end - start) + start;
}



void Pipeline::LoadVertex(float* vertex)
{
	vertexIn = vertex;
}
void Pipeline::LoadTexCoord(float* textureCoord)
{
	texcoord = textureCoord;
}

void Pipeline::setMVPMat(glm::mat4 mvp)
{
	MVP = mvp;
}

void Pipeline::runVertexShader()
{
	for (auto i = primitive.begin(); i != primitive.end(); i++)
	{
		i->p1 = MVP * i->p1;
		i->p2 = MVP * i->p2;
		i->p3 = MVP * i->p3;
	}
}

void Pipeline::runPerspectiveDivide()
{
	for (auto i = primitive.begin(); i != primitive.end(); i++)
	{
		i->p1 /= i->p1.w;
		i->p2 /= i->p2.w;
		i->p3 /= i->p3.w;
	}
}

#define INBOUND_X(p1) (p1.x <= 1.0 && p1.x >= -1.0)
#define INBOUND_Y(p1) (p1.y <= 1.0 && p1.y >= -1.0)
#define INBOUND_Z(p1) (p1.z <= 1.0 && p1.z >= -1.0)

#define INBOUND(p1) INBOUND_X(p1) && INBOUND_Y(p1) && INBOUND_Z(p1)


void clip(Primitive primitive,std::list<Primitive>& list)
{
	if (INBOUND(primitive.p1) && INBOUND(primitive.p2) && INBOUND(primitive.p3))
	{
		list.push_back(primitive);
		return;
	}
	if (primitive.p1.x < -1.0)
	{
		float k1 = Interpolation(primitive.p1.x, primitive.p2.x, -1.0);
		float k2 = Interpolation(primitive.p1.x, primitive.p3.x, -1.0);
		
		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p1 = Interpolation(primitive.p1, primitive.p2, k1);
		newPrimitive1.uv1 = Interpolation(primitive.uv1, primitive.uv2, k1);
		newPrimitive2.p1 = Interpolation(primitive.p1, primitive.p3, k2);
		newPrimitive2.uv1 = Interpolation(primitive.uv1, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p1.x > 1.0)
	{
		float k1 = Interpolation(primitive.p1.x, primitive.p2.x, 1.0);
		float k2 = Interpolation(primitive.p1.x, primitive.p3.x, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p1 = Interpolation(primitive.p1, primitive.p2, k1);
		newPrimitive1.uv1 = Interpolation(primitive.uv1, primitive.uv2, k1);
		newPrimitive2.p1 = Interpolation(primitive.p1, primitive.p3, k2);
		newPrimitive2.uv1 = Interpolation(primitive.uv1, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p1.y < -1.0)
	{
		float k1 = Interpolation(primitive.p1.y, primitive.p2.y, -1.0);
		float k2 = Interpolation(primitive.p1.y, primitive.p3.y, -1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p1 = Interpolation(primitive.p1, primitive.p2, k1);
		newPrimitive1.uv1 = Interpolation(primitive.uv1, primitive.uv2, k1);
		newPrimitive2.p1 = Interpolation(primitive.p1, primitive.p3, k2);
		newPrimitive2.uv1 = Interpolation(primitive.uv1, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p1.y > 1.0)
	{
		float k1 = Interpolation(primitive.p1.y, primitive.p2.y, 1.0);
		float k2 = Interpolation(primitive.p1.y, primitive.p3.y, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p1 = Interpolation(primitive.p1, primitive.p2, k1);
		newPrimitive1.uv1 = Interpolation(primitive.uv1, primitive.uv2, k1);
		newPrimitive2.p1 = Interpolation(primitive.p1, primitive.p3, k2);
		newPrimitive2.uv1 = Interpolation(primitive.uv1, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p1.z < -1.0)
	{
		float k1 = Interpolation(primitive.p1.z, primitive.p2.z, -1.0);
		float k2 = Interpolation(primitive.p1.z, primitive.p3.z, -1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p1 = Interpolation(primitive.p1, primitive.p2, k1);
		newPrimitive1.uv1 = Interpolation(primitive.uv1, primitive.uv2, k1);
		newPrimitive2.p1 = Interpolation(primitive.p1, primitive.p3, k2);
		newPrimitive2.uv1 = Interpolation(primitive.uv1, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p1.z > 1.0)
	{
		float k1 = Interpolation(primitive.p1.z, primitive.p2.z, 1.0);
		float k2 = Interpolation(primitive.p1.z, primitive.p3.z, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p1 = Interpolation(primitive.p1, primitive.p2, k1);
		newPrimitive1.uv1 = Interpolation(primitive.uv1, primitive.uv2, k1);
		newPrimitive2.p1 = Interpolation(primitive.p1, primitive.p3, k2);
		newPrimitive2.uv1 = Interpolation(primitive.uv1, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	/////////////////////////////

	if (primitive.p2.x < -1.0)
	{
		float k1 = Interpolation(primitive.p2.x, primitive.p1.x, -1.0);
		float k2 = Interpolation(primitive.p2.x, primitive.p3.x, -1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p2 = Interpolation(primitive.p2, primitive.p1, k1);
		newPrimitive1.uv2 = Interpolation(primitive.uv2, primitive.uv1, k1);
		newPrimitive2.p2 = Interpolation(primitive.p2, primitive.p3, k2);
		newPrimitive2.uv2 = Interpolation(primitive.uv2, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p2.x > 1.0)
	{
		float k1 = Interpolation(primitive.p2.x, primitive.p1.x, 1.0);
		float k2 = Interpolation(primitive.p2.x, primitive.p3.x, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p2 = Interpolation(primitive.p2, primitive.p1, k1);
		newPrimitive1.uv2 = Interpolation(primitive.uv2, primitive.uv1, k1);
		newPrimitive2.p2 = Interpolation(primitive.p2, primitive.p3, k2);
		newPrimitive2.uv2 = Interpolation(primitive.uv2, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p2.y < -1.0)
	{
		float k1 = Interpolation(primitive.p2.y, primitive.p1.y, -1.0);
		float k2 = Interpolation(primitive.p2.y, primitive.p3.y, -1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p2 = Interpolation(primitive.p2, primitive.p1, k1);
		newPrimitive1.uv2 = Interpolation(primitive.uv2, primitive.uv1, k1);
		newPrimitive2.p2 = Interpolation(primitive.p2, primitive.p3, k2);
		newPrimitive2.uv2 = Interpolation(primitive.uv2, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p2.y > 1.0)
	{
		float k1 = Interpolation(primitive.p2.y, primitive.p1.y, 1.0);
		float k2 = Interpolation(primitive.p2.y, primitive.p3.y, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p2 = Interpolation(primitive.p2, primitive.p1, k1);
		newPrimitive1.uv2 = Interpolation(primitive.uv2, primitive.uv1, k1);
		newPrimitive2.p2 = Interpolation(primitive.p2, primitive.p3, k2);
		newPrimitive2.uv2 = Interpolation(primitive.uv2, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p2.z < -1.0)
	{
		float k1 = Interpolation(primitive.p2.z, primitive.p1.z, -1.0);
		float k2 = Interpolation(primitive.p2.z, primitive.p3.z, -1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p2 = Interpolation(primitive.p2, primitive.p1, k1);
		newPrimitive1.uv2 = Interpolation(primitive.uv2, primitive.uv1, k1);
		newPrimitive2.p2 = Interpolation(primitive.p2, primitive.p3, k2);
		newPrimitive2.uv2 = Interpolation(primitive.uv2, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p2.z > 1.0)
	{
		float k1 = Interpolation(primitive.p2.z, primitive.p1.z, 1.0);
		float k2 = Interpolation(primitive.p2.z, primitive.p3.z, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p2 = Interpolation(primitive.p2, primitive.p1, k1);
		newPrimitive1.uv2 = Interpolation(primitive.uv2, primitive.uv1, k1);
		newPrimitive2.p2 = Interpolation(primitive.p2, primitive.p3, k2);
		newPrimitive2.uv2 = Interpolation(primitive.uv2, primitive.uv3, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	///////////////
	if (primitive.p3.x < -1.0)
	{
		float k1 = Interpolation(primitive.p3.x, primitive.p1.x, -1.0);
		float k2 = Interpolation(primitive.p3.x, primitive.p2.x, -1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p3 = Interpolation(primitive.p3, primitive.p1, k1);
		newPrimitive1.uv3 = Interpolation(primitive.uv3, primitive.uv1, k1);
		newPrimitive2.p3 = Interpolation(primitive.p3, primitive.p2, k2);
		newPrimitive2.uv3 = Interpolation(primitive.uv3, primitive.uv2, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p3.x > 1.0)
	{
		float k1 = Interpolation(primitive.p3.x, primitive.p1.x, 1.0);
		float k2 = Interpolation(primitive.p3.x, primitive.p2.x, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p3 = Interpolation(primitive.p3, primitive.p1, k1);
		newPrimitive1.uv3 = Interpolation(primitive.uv3, primitive.uv1, k1);
		newPrimitive2.p3 = Interpolation(primitive.p3, primitive.p2, k2);
		newPrimitive2.uv3 = Interpolation(primitive.uv3, primitive.uv2, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p3.y < -1.0)
	{
		float k1 = Interpolation(primitive.p3.y, primitive.p1.y, -1.0);
		float k2 = Interpolation(primitive.p3.y, primitive.p2.y, -1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p3 = Interpolation(primitive.p3, primitive.p1, k1);
		newPrimitive1.uv3 = Interpolation(primitive.uv3, primitive.uv1, k1);
		newPrimitive2.p3 = Interpolation(primitive.p3, primitive.p2, k2);
		newPrimitive2.uv3 = Interpolation(primitive.uv3, primitive.uv2, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p3.y > 1.0)
	{
		float k1 = Interpolation(primitive.p3.y, primitive.p1.y, 1.0);
		float k2 = Interpolation(primitive.p3.y, primitive.p2.y, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p3 = Interpolation(primitive.p3, primitive.p1, k1);
		newPrimitive1.uv3 = Interpolation(primitive.uv3, primitive.uv1, k1);
		newPrimitive2.p3 = Interpolation(primitive.p3, primitive.p2, k2);
		newPrimitive2.uv3 = Interpolation(primitive.uv3, primitive.uv2, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p3.z < -1.0)
	{
		float k1 = Interpolation(primitive.p3.z, primitive.p1.z, -1.0);
		float k2 = Interpolation(primitive.p3.z, primitive.p2.z, -1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p3 = Interpolation(primitive.p3, primitive.p1, k1);
		newPrimitive1.uv3 = Interpolation(primitive.uv3, primitive.uv1, k1);
		newPrimitive2.p3 = Interpolation(primitive.p3, primitive.p2, k2);
		newPrimitive2.uv3 = Interpolation(primitive.uv3, primitive.uv2, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
	if (primitive.p3.z > 1.0)
	{
		float k1 = Interpolation(primitive.p3.z, primitive.p1.z, 1.0);
		float k2 = Interpolation(primitive.p3.z, primitive.p2.z, 1.0);

		Primitive newPrimitive1, newPrimitive2;
		newPrimitive1 = primitive;
		newPrimitive2 = primitive;
		newPrimitive1.p3 = Interpolation(primitive.p3, primitive.p1, k1);
		newPrimitive1.uv3 = Interpolation(primitive.uv3, primitive.uv1, k1);
		newPrimitive2.p3 = Interpolation(primitive.p3, primitive.p2, k2);
		newPrimitive2.uv3 = Interpolation(primitive.uv3, primitive.uv2, k2);
		clip(newPrimitive1, list);
		clip(newPrimitive2, list);
		return;
	}
}


void Pipeline::runClip()
{
	for (auto it = primitive.begin(); it != primitive.end();)
	{
		bool pass_p1 = 0;
		bool pass_p2 = 0;
		bool pass_p3 = 0;
		std::list<Primitive> list;
		if (INBOUND(it->p1))
			pass_p1 = 1;
		if (INBOUND(it->p2))
			pass_p2 = 1;
		if (INBOUND(it->p3))
			pass_p3 = 1;
		if (pass_p1 && pass_p2 && pass_p3)
		{
			it++;
			continue;
		}
		if (!pass_p1 && !pass_p2 && !pass_p3)
		{
			it = primitive.erase(it);
			continue;
		}
		Primitive current = *it;
		clip(current, list);
		if (list.size() == 1)
		{
			it++; 
//			list.clear();
			continue;
		}
		primitive.splice(it, list);
		it = primitive.erase(it);
//		list.clear();
	}
}

void Pipeline::runPipeline(int count)
{
	assert(vertexIn != NULL);
	assert(texcoord != NULL);
	primitive.clear();
	for (int i = 0; i < count; i++)
	{
		Primitive pushback;

		pushback.p1 = glm::vec4(vertexIn[9 * i], vertexIn[9 * i + 1], vertexIn[9 * i + 2], 1.0);
		pushback.uv1 = glm::vec2(texcoord[6 * i], texcoord[6 * i + 1]);

		pushback.p2 = glm::vec4(vertexIn[9 * i + 3], vertexIn[9 * i + 4], vertexIn[9 * i + 5], 1.0);
		pushback.uv2 = glm::vec2(texcoord[6 * i + 2], texcoord[6 * i + 3]);

		pushback.p3 = glm::vec4(vertexIn[9 * i + 6], vertexIn[9 * i + 7], vertexIn[9 * i + 8], 1.0);
		pushback.uv3 = glm::vec2(texcoord[6 * i + 4], texcoord[6 * i + 5]);

		primitive.push_back(pushback);
	}

	runVertexShader();    //Multiple the MVP matrix.
	runPerspectiveDivide();   // PerspectiveDivide
	runClip();
	for (auto it = primitive.begin(); it != primitive.end(); it++)
	{
		engine->drawPrimitive(*it, texture);
	}
}