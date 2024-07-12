#pragma once
#include <glm/glm.hpp>

class Light {
private:
public:
	Light(class Renderer* renderer);
	Light(class Renderer* renderer, float& i, glm::vec4& c);
	~Light() {};

	glm::vec3 mIntensity;
	glm::vec4 mColor;
	glm::vec3 mPosition;
	class Renderer* mRenderer;
	virtual glm::mat4 GetMVP();
};

class DirectionLight : public Light {
public:
	DirectionLight(class Renderer* renderer);
	DirectionLight(class Renderer* renderer, float& _intensity, glm::vec4& _color);
	~DirectionLight();
	glm::vec3 mTarget;
	glm::vec3 mUp;
	void SetTargetAndUp(const glm::vec3& _target, const glm::vec3& _up);
	glm::mat4 GetMVP(class Actor* targetObject);
	//glm::mat4 GetMVP() override;
};

class PointLight :public Light {
public:
	PointLight(class Renderer* renderer);
	PointLight(class Renderer* renderer, float& _intensity, glm::vec4& _color, float& _radius);
	~PointLight();
	float mRadius;
	glm::mat4 GetMVP() override;
};