#pragma once
#include <string>

class Mesh {
public:
	Mesh(class VertexArray* va);
	~Mesh();

	void Unload();

	class VertexArray* GetVertexArray() { return mVertexArray; }
	//const std::string& GetShaderName() const { return mShaderName; }

	void SetMeshName(const std::string& name) { mMeshName = name; }
	std::string GetMeshName() const { return mMeshName; }

	//void SetMaterialName(const std::string& name) { mMaterialName = name; }
	//std::string GetMaterialName() const { return mMaterialName; }*/

private:
	class VertexArray* mVertexArray;
	//std::string mShaderName;
	//std::string mMaterialName;
	std::string mMeshName;
};