#include "LightComponent.h"
#include "Core/Actor.h"
#include <glm/glm.hpp>
#include "MyMath.h"

LightComponent::LightComponent(Actor* owner)
	: Component(owner)
	, mColor(glm::vec3(1.f))
	, mIntensity(glm::vec3(10.f))
	, mSpeed(10.f)
{
	SetTargetAndUp(glm::vec3(0.f, 0.f, 0.f), MyMath::AxisY);
}

LightComponent::~LightComponent()
{
}

void LightComponent::SetTargetAndUp(const glm::vec3& _target, const glm::vec3& _up)
{
	mTarget = _target;
	glm::vec3 side = glm::cross(mTarget - GetOwner()->GetPosition(), _up);
	mUp = glm::cross(side, mTarget - GetOwner()->GetPosition());
}

glm::mat4 LightComponent::GetMVP(Actor* targetObject)
{
	glm::mat4  lightMVP = targetObject->GetWorldTransform();
	glm::mat4 view = glm::lookAt(GetOwner()->GetPosition(), mTarget, mUp);
	glm::mat4 proj = glm::ortho(-200.f, 200.f, -200.f, 200.f, 0.1f, 1000.f);
	lightMVP = proj * view * lightMVP;

	return lightMVP;
}


void LightComponent::Update(float deltaTime)
{
	auto rotateMatrix = glm::rotate(glm::mat4(1.f), mSpeed, MyMath::AxisY);
	GetOwner()->SetPosition(rotateMatrix * glm::vec4(GetOwner()->GetPosition(), 1.f));
}