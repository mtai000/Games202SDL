#include "Light.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "Core/Renderer.h"
#include "Core/Actor.h"
Light::Light(Renderer* renderer)
	: mIntensity(10.f)
	, mColor(glm::vec4(1.f))
	, mRenderer(renderer)
{
}

Light::Light(Renderer* rendererm, float& i, glm::vec4& c)
	: mIntensity(i)
	, mColor(c)
	, mPosition(0.f, 10.f, 0.f)
{
}

glm::mat4 Light::GetMVP()
{
	return glm::mat4();
}

DirectionLight::DirectionLight(Renderer* renderer)
	:Light(renderer)
{
}

DirectionLight::DirectionLight(Renderer* renderer, float& _intensity, glm::vec4& _color)
	: Light(renderer, _intensity, _color)
{
}

DirectionLight::~DirectionLight()
{
}

PointLight::PointLight(Renderer* renderer)
	:Light(renderer), mRadius(1.f)
{
}

PointLight::PointLight(Renderer* renderer, float& _intensity, glm::vec4& _color, float& _radius)
	:Light(renderer, _intensity, _color), mRadius(_radius)
{
}

PointLight::~PointLight()
{
}

void DirectionLight::SetTargetAndUp(const glm::vec3& _target, const glm::vec3& _up)
{
	mTarget = _target;
	glm::vec3 side = glm::cross(mTarget - mPosition, _up);
	mUp = glm::cross(side, mTarget - mPosition);
}

glm::mat4 DirectionLight::GetMVP(Actor* targetObject)
{
	//glm::mat4 lightMVP = glm::mat4(1.f);
	glm::mat4  lightMVP = targetObject->GetWorldTransform();
	glm::mat4 view = glm::lookAt(mPosition, mTarget, mUp);
	//glm::mat4 proj = glm::ortho(0.f, (float)mRenderer->GetScreenWidth(), 0.f, (float)mRenderer->GetScreenHeight(), 0.1f, 1000.f);
	//glm::mat4 proj = glm::ortho(-500.f, 500.f, -500.f, 500.f, 0.1f, 1000.f);
	glm::mat4 proj = glm::ortho(-200.f, 200.f, -200.f, 200.f, 0.1f, 1000.f);
	lightMVP = proj * view * lightMVP;

	return lightMVP;
}


glm::mat4 PointLight::GetMVP()
{
	return glm::mat4();
}