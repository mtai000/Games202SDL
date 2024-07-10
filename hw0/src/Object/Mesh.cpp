#include "Mesh.h"
#include "Texture.h"

Mesh::Mesh(VertexArray* va)
{
	mVertexArray = va;
}

Mesh::~Mesh()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}

void Mesh::Unload() {
	delete mVertexArray;
	mVertexArray = nullptr;
}