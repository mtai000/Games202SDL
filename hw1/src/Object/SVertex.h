#pragma once
#include "head.h"

struct SVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	SVertex(float vx, float vy, float vz,
		float nx, float ny, float nz, float u, float v)
		: position(glm::vec3(vx, vy, vz))
		, normal(glm::vec3(nx, ny, nz))
		, texCoord(glm::vec2(u, v)) {};

	SVertex() : position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), texCoord(0.0f, 0.0f) {}
};