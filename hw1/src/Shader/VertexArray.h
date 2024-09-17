#pragma once

#include "head.h"

struct SVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};
class VertexArray {
public:

	VertexArray(const SVertex* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);

	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);

	~VertexArray();

	void SetActive();
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }


private:
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
};