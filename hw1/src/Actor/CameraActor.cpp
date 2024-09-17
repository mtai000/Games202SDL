#include "CameraActor.h"
#include "Core/Actor.h"
#include "Core/Game.h"
#include "Core/Renderer.h"
#include "head.h"
#include "Component/MoveComponent.h"
#include <glm/gtx/vector_angle.hpp>;
#include <glm/gtc/constants.hpp>

CameraActor::CameraActor(Game* _game)
	: Actor(_game)
	, mReCompute(true)
	, mFocusTar(glm::vec3(0.f, 20.f, 0.f))
{
	SetPosition(glm::vec3(20.f, 50.f, 50.f));
	mFov = 60.f;
	LookAt(mFocusTar);
	mAlwaysFocus = true;
}

CameraActor::~CameraActor()
{
}

void CameraActor::LookAt(glm::vec3 _tar)
{
	glm::vec3 direction = glm::normalize(GetPosition() - _tar);
	float angle = glm::angle(direction, (glm::vec3)mms::AxisY);

	if (angle < mms::EPSILON)
		direction = glm::normalize(glm::vec3(0.f, 1.f, -0.1f));
	auto side = glm::normalize(glm::cross(-direction, mms::AxisY));
	auto up = glm::normalize(glm::cross(side, -direction));

	mView = glm::lookAt(GetPosition(), _tar, up);

	mForward = -direction;
	mSide = -side;
	mUp = up;

	glm::vec3 rotate;
	rotate.x = asin(direction.y);    //Pitch  = asin(y/1)

	rotate.y = atan2(direction.z, direction.x);

	rotate.z = 0.f;    //Roll

	SetRotation(rotate);
}

glm::mat4 CameraActor::GetViewMatrix()
{
	if (mReCompute)
	{
		LookAt(GetPosition() + mForward * 1000.f);
		mReCompute = false;
	}
	return mView;
}

glm::mat4 CameraActor::GetProjMatrix()
{
	auto h = GetGame()->GetRenderer()->GetScreenHeight();
	auto w = GetGame()->GetRenderer()->GetScreenWidth();
	return glm::perspective(glm::radians(mFov), w / h, 0.1f, 1000.f);
}

void CameraActor::ActorInput(const uint8_t* keyState)
{
	float _right = 0.f;
	float _up = 0.f;
	if (keyState[SDL_SCANCODE_A])
	{
		_right += 400.f;
	}
	else if (keyState[SDL_SCANCODE_D])
	{
		_right -= 400.f;
	}
	else if (keyState[SDL_SCANCODE_W])
	{
		_up += 400.f;
	}
	else if (keyState[SDL_SCANCODE_S])
	{
		_up -= 400.f;
	}

	if (keyState[SDL_SCANCODE_F])
	{
		mAlwaysFocus = !mAlwaysFocus;
	}

	if (keyState[SDL_SCANCODE_R])
	{
		LookAt(mFocusTar);
	}

	mSideSpeed = _right;
	mUpSpeed = _up;
}

void CameraActor::Forward(int _y)
{
	mForwadSpeed = _y * 400.f;
}

void CameraActor::UpdateActor(float deltaTime) {

	if (abs(mForwadSpeed) > mms::EPSILON)
	{
		mReCompute = true;
		SetPosition(GetPosition() + mForward * mForwadSpeed * deltaTime);
	}

	if (mAlwaysFocus)
	{	
		if (abs(mSideSpeed) > mms::EPSILON)
		{
			mReCompute = true;
			auto newPos = glm::rotate(glm::mat4(1.f), glm::radians(mSideSpeed / 4 * deltaTime), mms::AxisY) * glm::vec4(GetPosition(), 1.0f);
			SetPosition(glm::vec3(newPos.x, newPos.y, newPos.z));
		}
		if (abs(mUpSpeed) > mms::EPSILON)
		{
			mReCompute = true;
			auto newPos = glm::rotate(glm::mat4(1.f), glm::radians(mUpSpeed / 4 * deltaTime), mSide) * glm::vec4(GetPosition(), 1.0f);
			SetPosition(glm::vec3(newPos.x, newPos.y, newPos.z));
		}
		LookAt(mFocusTar);
	}
	else
	{
		if (abs(mSideSpeed) > mms::EPSILON)
		{
			mReCompute = true;
			SetPosition(GetPosition() + mSide * mSideSpeed * deltaTime);
		}
		if (abs(mUpSpeed) > mms::EPSILON)
		{
			mReCompute = true;
			SetPosition(GetPosition() + mUp * mUpSpeed * deltaTime);
		}
	}


}
