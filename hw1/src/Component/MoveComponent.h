#pragma once
#include "Core/Component.h"

class MoveComponent :public Component {
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetMoveSpeed() const { return mMoveSpeed; }
	float GetRotateSpeed() const { return mRotateSpeed; }

	void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
	void SetRotateSpeed(float speed) { mRotateSpeed = speed; }
private:

	float mRotateSpeed;
	float mMoveSpeed;

};