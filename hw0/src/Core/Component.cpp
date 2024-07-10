#include "Component.h"
#include "Core/Actor.h"

Component::Component(Actor* owner, int updateOrder)
	: mOwner(owner)
	, mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

