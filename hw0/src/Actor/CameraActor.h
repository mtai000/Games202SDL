#pragma once
#include "Core/Actor.h"
#include <glm/glm.hpp>
class CameraActor :public Actor {
public:
	CameraActor(class Game* _game);
	~CameraActor();

	void LookAt(glm::vec3);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
private:
	class MoveComponent* mMoveComp;
	glm::mat4 mView;
	glm::mat4 mProj;
	float mFov;
};