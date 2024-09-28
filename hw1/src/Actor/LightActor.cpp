#include "LightActor.h"
#include "Component/MeshComponent.h"
#include "Component/LightComponent.h"
#include "Component/FrameBufferComponent.h"
#include <glm/glm.hpp>
#include "Core/Game.h"
#include "Core/Renderer.h"
#include "Object/Mesh.h"
#include "Object/Material.h"

LightActor::LightActor(Game* _game, glm::vec3 pos)
	: Actor(_game)
	, mMeshComp(NULL)
	, mFrameBufferComp(NULL)
{
	SetPosition(pos);
	mLightComp = new LightComponent(this);
}

LightActor::~LightActor()
{
}

void LightActor::InitFrameBuffer(unsigned int width, unsigned int height) {
	if (!mFrameBufferComp)
		mFrameBufferComp = new FrameBufferComponent(this, width, height);
}

void LightActor::ResetPosition(glm::vec3 newPos)
{
	SetPosition(newPos);
	mLightComp->SetTargetAndUp();
}

void LightActor::SetRotateSpeed(float _v)
{
	mLightComp->SetSpeed(_v);
}

LightComponent* LightActor::GetLightComponent(){
	return mLightComp;
}