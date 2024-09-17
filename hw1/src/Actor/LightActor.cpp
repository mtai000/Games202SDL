#include "LightActor.h"
#include "Component/MeshComponent.h"
#include "Component/LightComponent.h"
#include "Component/FrameBufferComponent.h"

#include <glm/glm.hpp>

LightActor::LightActor(Game* _game)
	: Actor(_game)
	, mMeshComp(NULL)
	, mFrameBufferComp(NULL)
{
	SetPosition(glm::vec3(10.f, 10.f, 0.f));

	mLightComp = new LightComponent(this);
	mLightComp->SetColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	mLightComp->SetIntensity(glm::vec3(10.f, 10.f, 10.f));

	//mMeshComp = new MeshComponent(this);
	//mMeshComp->GenCube();
}

LightActor::LightActor(Game* _game, glm::vec3 pos)
	:Actor(_game)
	, mMeshComp(NULL)
	, mFrameBufferComp(NULL)
{
	SetPosition(pos);

	mLightComp = new LightComponent(this);
	mLightComp->SetColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	mLightComp->SetIntensity(glm::vec3(10.f, 10.f, 10.f));
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
