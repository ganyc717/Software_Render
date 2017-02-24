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

bool checkStatus(glm::vec4 position, int status)
{
	switch (status) {
	case STATUS_X_OUT_NEGTIVE:
		return position.x < -1;
	case STATUS_X_OUT_POSITIVE:
		return position.x > 1;
	case STATUS_Y_OUT_NEGTIVE:
		return position.y < -1;
	case STATUS_Y_OUT_POSITIVE:
		return position.y > 1;
	case STATUS_Z_OUT_NEGTIVE:
		return position.z < -1;
	case STATUS_Z_OUT_POSITIVE:
		return position.z > 1;
	case STATUS_IN_BOUND:
		return INBOUND(position);
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
			i->position[j] /= i->position[j].w;
}

void clip(Primitive primitive, std::list<Primitive>& list);
void clip_OnePointOutOfBound(Primitive primitive, std::list<Primitive>& list, int outofboundPointPosition, int status)
{
	float start, endA, endB, middle;
	int A = -1;
	int B = -1;

	start = primitive.position[outofboundPointPosition][status / 2];
	switch (outofboundPointPosition)
	{
	case 0:
		A = 1; B = 2; break;
	case 1:
		A = 0; B = 2; break;
	case 2:
		A = 0; B = 1; break;
	default:
		break;
	}// Get the other 2 point index
	assert(A != -1);
	assert(B != -1);
	if (status % 2 == 0)
		middle = -1.0;     // negtive out of bound
	else
		middle = 1.0;      // positive out of bound
	start = primitive.position[outofboundPointPosition][status / 2];
	endA = primitive.position[A][status / 2];
	endB = primitive.position[B][status / 2];
	float kA = Interpolation(start, endA, middle);
	float kB = Interpolation(start, endB, middle);
	glm::vec4 newPosition1 = Interpolation(primitive.position[outofboundPointPosition], primitive.position[A], kA);
	glm::vec4 newPosition2 = Interpolation(primitive.position[outofboundPointPosition], primitive.position[B], kB);
	glm::vec2 newUV1 = Interpolation(primitive.uv[outofboundPointPosition], primitive.uv[A], kA);
	glm::vec2 newUV2 = Interpolation(primitive.uv[outofboundPointPosition], primitive.uv[B], kB);
	Primitive newPrimitive1, newPrimitive2;

	newPrimitive1 = primitive;
	newPrimitive1.position[outofboundPointPosition] = newPosition1;
	newPrimitive1.uv[outofboundPointPosition] = newUV1;
	newPrimitive2.position[0] = newPosition2;
	newPrimitive2.position[1] = newPosition1;
	newPrimitive2.position[2] = primitive.position[B];
	newPrimitive2.uv[0] = newUV2;
	newPrimitive2.uv[1] = newUV1;
	newPrimitive2.uv[2] = primitive.uv[B];
	clip(newPrimitive1, list);
	clip(newPrimitive2, list);
}
void clip_TwoPointOutOfBound(Primitive primitive, std::list<Primitive>& list, int outofboundPointPosition1, int outofboundPointPosition2, int status) //
{
	int inboundPointPosition = 3 - outofboundPointPosition1 - outofboundPointPosition2;
	float startA, startB, end, middle;

	if (status % 2 == 0)
		middle = -1.0;     // negtive out of bound
	else
		middle = 1.0;      // positive out of bound
	startA = primitive.position[outofboundPointPosition1][status / 2];
	startB = primitive.position[outofboundPointPosition2][status / 2];
	end = primitive.position[inboundPointPosition][status / 2];
	float kA = Interpolation(startA, end, middle);
	float kB = Interpolation(startB, end, middle);
	glm::vec4 newPosition1 = Interpolation(primitive.position[outofboundPointPosition1], primitive.position[inboundPointPosition], kA);
	glm::vec4 newPosition2 = Interpolation(primitive.position[outofboundPointPosition2], primitive.position[inboundPointPosition], kB);
	glm::vec2 newUV1 = Interpolation(primitive.uv[outofboundPointPosition1], primitive.uv[inboundPointPosition], kA);
	glm::vec2 newUV2 = Interpolation(primitive.uv[outofboundPointPosition2], primitive.uv[inboundPointPosition], kB);
	Primitive newPrimitive;
	newPrimitive.position[outofboundPointPosition1] = newPosition1;
	newPrimitive.position[outofboundPointPosition2] = newPosition2;
	newPrimitive.position[inboundPointPosition] = primitive.position[inboundPointPosition];
	newPrimitive.uv[outofboundPointPosition1] = newUV1;
	newPrimitive.uv[outofboundPointPosition2] = newUV2;
	newPrimitive.uv[inboundPointPosition] = primitive.uv[inboundPointPosition];
	clip(newPrimitive, list);
}

void clip(Primitive primitive, std::list<Primitive>& list, int status, int point)
{
	int A = -1;
	int B = -1;
	if (!checkStatus(primitive.position[point], status))
		return;
	switch (point)
	{
	case 0:
		A = 1; B = 2; break;
	case 1:
		A = 0; B = 2; break;
	case 2:
		A = 1; B = 2; break;
	default:
		break;
	}
	int statusA = checkStatus(primitive.position[A],status);
	int statusB = checkStatus(primitive.position[B], status);
	if (statusA + statusB == 0)
	{
		clip_OnePointOutOfBound(primitive, list, point, status);
		return;
	}
	if (statusA + statusB == 2)
		return;
	if (statusA == 1)
	{
		clip_TwoPointOutOfBound(primitive, list, A, point, status);
		return;
	}
	if (statusB == 1)
	{
		clip_TwoPointOutOfBound(primitive, list, B, point, status);
		return;
	}
}


void clip(Primitive primitive,std::list<Primitive>& list)
{

	if (INBOUND(primitive.position[0]) && INBOUND(primitive.position[1]) && INBOUND(primitive.position[2]))   // All in bound
	{
		list.push_back(primitive);
		return;
	}

	clip(primitive, list, STATUS_X_OUT_NEGTIVE, 0);
	clip(primitive, list, STATUS_X_OUT_POSITIVE, 0);
	clip(primitive, list, STATUS_Y_OUT_NEGTIVE, 0);
	clip(primitive, list, STATUS_Y_OUT_POSITIVE, 0);
	clip(primitive, list, STATUS_Z_OUT_NEGTIVE, 0);
	clip(primitive, list, STATUS_Z_OUT_POSITIVE, 0);

	clip(primitive, list, STATUS_X_OUT_NEGTIVE, 1);
	clip(primitive, list, STATUS_X_OUT_POSITIVE, 1);
	clip(primitive, list, STATUS_Y_OUT_NEGTIVE, 1);
	clip(primitive, list, STATUS_Y_OUT_POSITIVE, 1);
	clip(primitive, list, STATUS_Z_OUT_NEGTIVE, 1);
	clip(primitive, list, STATUS_Z_OUT_POSITIVE, 1);

	clip(primitive, list, STATUS_X_OUT_NEGTIVE, 2);
	clip(primitive, list, STATUS_X_OUT_POSITIVE, 2);
	clip(primitive, list, STATUS_Y_OUT_NEGTIVE, 2);
	clip(primitive, list, STATUS_Y_OUT_POSITIVE, 2);
	clip(primitive, list, STATUS_Z_OUT_NEGTIVE, 2);
	clip(primitive, list, STATUS_Z_OUT_POSITIVE, 2);
}


void Pipeline::runClip()
{
	for (auto it = primitive.begin(); it != primitive.end();)
	{
		std::list<Primitive> list;
		Primitive current = *it;
		clip(current, list);
		primitive.splice(it, list);
		it = primitive.erase(it);
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

		pushback.position[0] = glm::vec4(vertexIn[9 * i], vertexIn[9 * i + 1], vertexIn[9 * i + 2], 1.0);
		pushback.uv[0] = glm::vec2(texcoord[6 * i], texcoord[6 * i + 1]);

		pushback.position[1] = glm::vec4(vertexIn[9 * i + 3], vertexIn[9 * i + 4], vertexIn[9 * i + 5], 1.0);
		pushback.uv[1] = glm::vec2(texcoord[6 * i + 2], texcoord[6 * i + 3]);

		pushback.position[2] = glm::vec4(vertexIn[9 * i + 6], vertexIn[9 * i + 7], vertexIn[9 * i + 8], 1.0);
		pushback.uv[2] = glm::vec2(texcoord[6 * i + 4], texcoord[6 * i + 5]);

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