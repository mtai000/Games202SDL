#include "MeshComponent.h"
#include "Shader/Shader.h"
#include "Core/Component.h"
#include "Core/Actor.h"
#include "Core/Game.h"
#include "Core/Renderer.h"
#include "Object/Mesh.h"
#include <Shader/VertexArray.h>
#include "Actor/CameraActor.h"

MeshComponent::MeshComponent(Actor* owner)
	:Component(owner)
	, mMesh(nullptr)
	, mMaterial(nullptr)
	, mVisible(true)
{
	GetOwner()->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
	GetOwner()->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::GenCube()
{
}

void MeshComponent::Draw(Shader* meshShader)
{
	if (mMesh) {
		mMesh->GetVertexArray()->SetActive();
		glDrawElements(GL_TRIANGLES, mMesh->GetVertexArray()->GetNumIndices(), GL_UNSIGNED_INT, 0);
	}
}
