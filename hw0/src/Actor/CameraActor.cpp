#include "CameraActor.h"
#include "Core/Actor.h"
#include "Core/Game.h"
#include "Core/Renderer.h"
#include "MyMath.h"
#include "Component/MoveComponent.h"
#include <glm/gtx/vector_angle.hpp>

CameraActor::CameraActor(Game* _game)
	: Actor(_game)
{
	mMoveComp = new MoveComponent(this);
	SetPosition(glm::vec3(20.f, 50.f, 50.f));
	mFov = 60.f;
	LookAt(glm::vec3(0.f));
}

CameraActor::~CameraActor()
{
}

void CameraActor::LookAt(glm::vec3 _tar)
{
	glm::vec3 direction = glm::normalize(GetPosition() - _tar);
	float angle = glm::angle(direction, (glm::vec3)MyMath::AxisY);

	if (angle < MyMath::EPSILON)
		direction = glm::normalize(glm::vec3(0.f, 1.f, -0.1f));
	auto side = glm::normalize(glm::cross(-direction, MyMath::AxisY));
	auto up = glm::normalize(glm::cross(side, -direction));

	mView = glm::lookAt(GetPosition(), _tar, up);
	glm::vec3 rotate;
	rotate.x = asin(direction.y);    //Pitch  = asin(y/1)

	rotate.y = atan2(direction.z, direction.x);

	rotate.z = 0.f;    //Roll

	SetRotation(rotate);
}

glm::mat4 CameraActor::GetViewMatrix()
{
	return mView;
}

glm::mat4 CameraActor::GetProjMatrix()
{
	auto h = GetGame()->GetRenderer()->GetScreenHeight();
	auto w = GetGame()->GetRenderer()->GetScreenWidth();
	return glm::perspective(glm::radians(mFov), w / h, 0.1f, 1000.f);
}


