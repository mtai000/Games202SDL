#include "Actor.h"
#include "Core/Game.h"
#include "Core/Component.h"
#include "Component/MeshComponent.h"
#include <typeinfo>

Actor::Actor(Game* game)
	: mState(EActive)
	, mPosition(glm::vec3(0.f))
	, mRotation(glm::vec3(0.f))
	, mScale(1.f)
	, mGame(game)
	, mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor() {
	mGame->RemoveActor(this);
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive) {
		ComputeWorldTransform();

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform) {
		mRecomputeWorldTransform = false;

		mWorldTransform = glm::scale(glm::mat4(1.f), mScale);
		mWorldTransform *= glm::eulerAngleXYZ(glm::radians(mRotation.x)
			, glm::radians(mRotation.y)
			, glm::radians(mRotation.z));
		mWorldTransform *= glm::translate(glm::mat4(1.f), mPosition);

		for (auto comp : mComponents) {
			comp->OnUpdateWorldTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {
		if (myOrder < (*iter)->GetUpdateOrder())
			break;
	}
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

