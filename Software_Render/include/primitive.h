#pragma once
#include<glm\glm.hpp>
struct Primitive
{
	glm::vec4 position[3];
	glm::vec2 uv[3];
};

#define INBOUND_X(p1) (p1.x <= 1.0 && p1.x >= -1.0)
#define INBOUND_Y(p1) (p1.y <= 1.0 && p1.y >= -1.0)
#define INBOUND_Z(p1) (p1.z <= 1.0 && p1.z >= -1.0)

#define INBOUND(p1) (INBOUND_X(p1) && INBOUND_Y(p1) && INBOUND_Z(p1))



#define STATUS_X_OUT_NEGTIVE  0
#define STATUS_X_OUT_POSITIVE 1
#define STATUS_Y_OUT_NEGTIVE  2
#define STATUS_Y_OUT_POSITIVE 3
#define STATUS_Z_OUT_NEGTIVE  4
#define STATUS_Z_OUT_POSITIVE 5
#define STATUS_IN_BOUND       6
#define STATUS_NOT_DEFINE     7


