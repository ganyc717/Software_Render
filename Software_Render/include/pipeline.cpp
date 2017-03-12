#include"pipeline.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

float getLambda(glm::vec2 start, glm::vec2 end, int direction)
{
	assert(direction == 1 || direction == -1);
	glm::mat2 mat = glm::mat2(end - start, glm::vec2(1, direction));
	return (-glm::inverse(mat) * start).x;
}
/*
middle = start + lambda * (end -  start);
*/
glm::vec4 getMiddlePoint(glm::vec4 start, glm::vec4 end, float k)
{
	return k * (end - start) + start;
}
glm::vec2 getMiddlePoint(glm::vec2 start, glm::vec2 end, float k)
{
	return k * (end - start) + start;
}

bool checkStatus(glm::vec4 position, int status)
{
	float bound = position.w;
	switch (status) {
	case STATUS_X_OUT_NEGTIVE:
		return position.x < -bound;
	case STATUS_X_OUT_POSITIVE:
		return position.x > bound;
	case STATUS_Y_OUT_NEGTIVE:
		return position.y < -bound;
	case STATUS_Y_OUT_POSITIVE:
		return position.y > bound;
	case STATUS_Z_OUT_NEGTIVE:
		return position.z < -bound;
	case STATUS_Z_OUT_POSITIVE:
		return position.z > bound;
	default:
		return false;
	}
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
		for (int j = 0; j < 3;j++)
			i->position[j] = MVP * i->position[j];
}

void Pipeline::runPerspectiveDivide()
{
	for (auto i = primitive.begin(); i != primitive.end(); i++)
		for (int j = 0; j < 3; j++)
		{
			i->position[j] /= i->position[j].w;
			for (int k = 0; k < 4; k++)
			{
				if (glm::abs(i->position[j][k]) > 1.0)
					if (i->position[j][k] > 0)
						i->position[j][k] = 1.0;
					else
						i->position[j][k] = -1.0;
			}//Sometimes the precision is not enough, so make sure the coordinate is in the [-1,1]
		}
}


void clip_OnePointOutOfBound(std::list<Primitive>::iterator& it, std::list<Primitive>& list, int outofboundPointPosition, int status)
{

	int A = -1;
	int B = -1;
	int direction;
	switch (outofboundPointPosition)
	{
	case 0:
		A = 1; B = 2; break;
	case 1:
		A = 2; B = 0; break;
	case 2:
		A = 0; B = 1; break;
	default:
		break;
	}// Get the other 2 point index
	assert(A != -1);
	assert(B != -1);
	if (status % 2 == 0)
		direction = -1;     // negtive out of bound
	else
		direction = 1;      // positive out of bound
	glm::vec2 start = glm::vec2(it->position[outofboundPointPosition][status / 2], it->position[outofboundPointPosition][3]);
	glm::vec2 endA = glm::vec2(it->position[A][status / 2], it->position[A][3]);
	glm::vec2 endB = glm::vec2(it->position[B][status / 2], it->position[B][3]);
	float lambdaA = getLambda(start, endA, direction);
	float lambdaB = getLambda(start, endB, direction);

	glm::vec4 newPosition1 = getMiddlePoint(it->position[outofboundPointPosition], it->position[A], lambdaA);
	glm::vec4 newPosition2 = getMiddlePoint(it->position[outofboundPointPosition], it->position[B], lambdaB);
	glm::vec2 newUV1 = getMiddlePoint(it->uv[outofboundPointPosition], it->uv[A], lambdaA);
	glm::vec2 newUV2 = getMiddlePoint(it->uv[outofboundPointPosition], it->uv[B], lambdaB);

	Primitive newPrimitive1, newPrimitive2;

	newPrimitive1.position[0] = newPosition1;
	newPrimitive1.position[1] = it->position[A];;
	newPrimitive1.position[2] = it->position[B];
	newPrimitive1.uv[0] = newUV1;
	newPrimitive1.uv[1] = it->uv[A];
	newPrimitive1.uv[2] = it->uv[B];

	newPrimitive2.position[0] = newPosition2;
	newPrimitive2.position[1] = newPosition1;
	newPrimitive2.position[2] = it->position[B];
	newPrimitive2.uv[0] = newUV2;
	newPrimitive2.uv[1] = newUV1;
	newPrimitive2.uv[2] = it->uv[B];

	list.insert(it, newPrimitive1);
	list.insert(it, newPrimitive2);
	it = list.erase(it);

}
void clip_TwoPointOutOfBound(std::list<Primitive>::iterator& it, std::list<Primitive>& list, int outofboundPointPosition1, int outofboundPointPosition2, int status) //
{
	int inboundPointPosition = 3 - outofboundPointPosition1 - outofboundPointPosition2;
	int direction;

	if (status % 2 == 0)
		direction = -1;     // negtive out of bound
	else
		direction = 1;      // positive out of bound
	glm::vec2 startA = glm::vec2(it->position[outofboundPointPosition1][status / 2], it->position[outofboundPointPosition1][3]);
	glm::vec2 startB = glm::vec2(it->position[outofboundPointPosition2][status / 2], it->position[outofboundPointPosition2][3]);
	glm::vec2 end = glm::vec2(it->position[inboundPointPosition][status / 2], it->position[inboundPointPosition][3]);
	float lambdaA = getLambda(startA, end, direction);
	float lambdaB = getLambda(startB, end, direction);

	glm::vec4 newPosition1 = getMiddlePoint(it->position[outofboundPointPosition1], it->position[inboundPointPosition], lambdaA);
	glm::vec2 newUV1 = getMiddlePoint(it->uv[outofboundPointPosition1], it->uv[inboundPointPosition], lambdaA);


	glm::vec4 newPosition2 = getMiddlePoint(it->position[outofboundPointPosition2], it->position[inboundPointPosition], lambdaB);
	glm::vec2 newUV2 = getMiddlePoint(it->uv[outofboundPointPosition2], it->uv[inboundPointPosition], lambdaB);


	Primitive newPrimitive;
	newPrimitive.position[outofboundPointPosition1] = newPosition1;
	newPrimitive.position[outofboundPointPosition2] = newPosition2;
	newPrimitive.position[inboundPointPosition] = it->position[inboundPointPosition];
	newPrimitive.uv[outofboundPointPosition1] = newUV1;
	newPrimitive.uv[outofboundPointPosition2] = newUV2;
	newPrimitive.uv[inboundPointPosition] = it->uv[inboundPointPosition];

	list.insert(it, newPrimitive);
	it = list.erase(it);

}

void clip(std::list<Primitive>& list, int status)
{
	for (auto it = list.begin(); it != list.end();)
	{
		int statusA = checkStatus(it->position[0], status);
		int statusB = checkStatus(it->position[1], status);
		int statusC = checkStatus(it->position[2], status);
		if (statusA + statusB + statusC == 3)//All out of bound, abandon it.
		{
			it = list.erase(it);
			continue;
		}
		if (statusA + statusB + statusC == 2)//Two point out of bound.
		{
			if (statusA == 0)
				clip_TwoPointOutOfBound(it, list, 1, 2, status);
			if (statusB == 0)
				clip_TwoPointOutOfBound(it, list, 2, 0, status);
			if (statusC == 0)
				clip_TwoPointOutOfBound(it, list, 0, 1, status);
			continue;
		}
		if (statusA + statusB + statusC == 1)//One point out of bound.
		{
			if (statusA == 1)
				clip_OnePointOutOfBound(it, list, 0, status);
			if (statusB == 1)
				clip_OnePointOutOfBound(it, list, 1, status);
			if (statusC == 1)
				clip_OnePointOutOfBound(it, list, 2, status);
			continue;
		}
		if (statusA + statusB + statusC == 0)//In bound.
		{
			it++;
		}
	}
}


void Pipeline::runClip()
{
	clip(primitive, STATUS_X_OUT_NEGTIVE);
	clip(primitive, STATUS_X_OUT_POSITIVE);
	clip(primitive, STATUS_Y_OUT_NEGTIVE);
	clip(primitive, STATUS_Y_OUT_POSITIVE);
	clip(primitive, STATUS_Z_OUT_NEGTIVE);
	clip(primitive, STATUS_Z_OUT_POSITIVE);
}


void Pipeline::runPipeline(int count)
{
	assert(vertexIn != NULL);
	assert(texcoord != NULL);
	primitive.clear();
	for (int i = 0; i < count; i++)
	{
		Primitive pushback;

		pushback.position[0] = glm::vec4(vertexIn[9 * i], vertexIn[9 * i + 1], vertexIn[9 * i + 2], 1.0);
		pushback.uv[0] = glm::vec2(texcoord[6 * i], texcoord[6 * i + 1]);

		pushback.position[1] = glm::vec4(vertexIn[9 * i + 3], vertexIn[9 * i + 4], vertexIn[9 * i + 5], 1.0);
		pushback.uv[1] = glm::vec2(texcoord[6 * i + 2], texcoord[6 * i + 3]);

		pushback.position[2] = glm::vec4(vertexIn[9 * i + 6], vertexIn[9 * i + 7], vertexIn[9 * i + 8], 1.0);
		pushback.uv[2] = glm::vec2(texcoord[6 * i + 4], texcoord[6 * i + 5]);

		primitive.push_back(pushback);
	}

	runVertexShader();    //Multiple the MVP matrix.
//	runPerspectiveDivide();   // PerspectiveDivide
	runClip();             // We need clip in the linear space first and then perspective divide otherwise here will be error.
	runPerspectiveDivide();// PerspectiveDivide
	for (auto it = primitive.begin(); it != primitive.end(); it++)
	{
		engine->drawPrimitive(*it, texture);
	}
}