#include "LightComponent.h"
#include "Core/Actor.h"
#include <glm/glm.hpp>

#include "Core/Game.h"
#include "Core/Renderer.h"
#include "Core/Actor.h"
#include "Core/Component.h"

LightComponent::LightComponent(Actor* owner)
	: Component(owner)
	, mColor(glm::vec3(1.f))
	, mIntensity(glm::vec3(10.f))
	, mSpeed(1.f)
{
	SetTargetAndUp(glm::vec3(0.f, 0.f, 0.f), mms::AxisY);
	GetOwner()->GetGame()->GetRenderer()->AddLightComp(this);
}

LightComponent::~LightComponent()
{
	GetOwner()->GetGame()->GetRenderer()->RemoveLightComp(this);
}



void LightComponent::SetTargetAndUp(const glm::vec3& _target, const glm::vec3& _up)
{
	mTarget = _target;
	glm::vec3 side = glm::cross(mTarget - GetOwner()->GetPosition(), _up);
	mUp = glm::cross(side, mTarget - GetOwner()->GetPosition());
}

glm::mat4 LightComponent::GetMVP(Actor* targetObject)
{
	targetObject->ComputeWorldTransform();
	glm::mat4 lightMVP = targetObject->GetWorldTransform();
	glm::mat4 view = glm::lookAt(GetOwner()->GetPosition(), mTarget, mUp);
	glm::mat4 proj = glm::ortho(-200.f, 400.f, -200.f, 400.f, 0.1f, 1000.f);
	lightMVP = proj * view * lightMVP;

	return lightMVP;
}


void LightComponent::Update(float deltaTime)
{
	auto rotateMatrix = glm::rotate(glm::mat4(1.f), mSpeed * deltaTime, mms::AxisY);
	GetOwner()->SetPosition(rotateMatrix * glm::vec4(GetOwner()->GetPosition(), 1.f));
}