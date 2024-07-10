#include "MoveComponent.h"
#include <MyMath.h>
#include <Core/Actor.h>

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mRotateSpeed(0.f)
	, mMoveSpeed(0.f)
{
}

void MoveComponent::Update(float deltaTime)
{
	if (MyMath::NearZero(mRotateSpeed)) {
		glm::vec3 rot = GetOwner()->GetRotation();
		float angle = mRotateSpeed * deltaTime;

		GetOwner()->SetRotation(rot);
	}
}
