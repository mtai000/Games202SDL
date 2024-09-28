#pragma once
#include "head.h"
#include <cstdint>
#include <glm/gtx/euler_angles.hpp>
#include <vector>

class Actor {
public:
	enum State {
		EActive,
		EPaused,
		EDead
	};
	Actor(class Game* game);

	virtual ~Actor();

	void Update(float deltaTime);

	virtual void UpdateActor(float deltaTime);

	void UpdateComponents(float deltaTime);

	void ProcessInput(const uint8_t* keyState);

	virtual void ActorInput(const uint8_t* keyState);

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	glm::vec3 GetScale() const { return mScale; }
	void SetScale(glm::vec3 scale) { mScale = scale;  mRecomputeWorldTransform = true; }


	glm::vec3& GetPosition() { return mPosition; }
	void SetPosition(const glm::vec3& position) {
		mPosition = position;
		mRecomputeWorldTransform = true;
	}

	const glm::vec3& GetRotation() const { return mRotation; }

	void SetRotation(const glm::vec3& rotation) {
		mRotation = rotation;
		mRecomputeWorldTransform = true;
	}

	glm::vec3 GetForward() const { return  glm::vec4(1.f, 0.f, 0.f, 1.f) * glm::eulerAngleYXZ(mRotation.x, mRotation.y, mRotation.z); }

	void ComputeWorldTransform();
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }

	class Game* GetGame() { return mGame; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState;


	glm::vec3 mPosition;
	glm::vec3 mRotation;  //ŷ����
	glm::mat4 mWorldTransform;

	glm::vec3 mScale;
	bool mRecomputeWorldTransform;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};