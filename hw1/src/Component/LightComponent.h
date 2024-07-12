#pragma once
#include "Core/Component.h"
#include <glm/glm.hpp>

class LightComponent : public Component {
public:
	LightComponent(class Actor* actor);
	~LightComponent();

	void SetColor(glm::vec3 _c) { mColor = _c; }
	glm::vec3 GetColor() const { return mColor; }

	void SetIntensity(glm::vec3 _i) { mIntensity = _i; }
	glm::vec3 GetIntensity() const { return mIntensity; }

	void SetTargetAndUp(const glm::vec3& _target, const glm::vec3& _up);
	glm::mat4 GetMVP(class Actor* targetObject);

	void Update(float deltaTime);

private:
	glm::vec3 mColor;
	glm::vec3 mIntensity;

	glm::vec3 mTarget;
	glm::vec3 mUp;
	float mSpeed;
};