#pragma once
#include "Core/Component.h"
#include <string>

class MeshComponent : public Component {
public:
	MeshComponent(class Actor* owner);
	~MeshComponent();

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }

	void SetMesh(class Mesh* mesh) { mMesh = mesh; }
	class Mesh* GetMesh() const { return mMesh; }

	void SetMaterial(class Material* material) { mMaterial = material; }
	Material* GetMaterial() { return mMaterial; }

	void SetTexture(class Texture* texture) { mTexture = texture; }
	class Texture* GetTexture() { return mTexture; }

	void Draw(class Shader* meshShader);
private:
	bool mVisible;
	class Mesh* mMesh;
	class Material* mMaterial;
	class Texture* mTexture;
};