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

	void ActorInput(const uint8_t* keyState) override;
	void Forward(int);
	void UpdateActor(float deltaTime);
	bool mReCompute;
private:
	class CameraControlComponent* mCamCtrl;
	glm::mat4 mView;
	glm::mat4 mProj;

	glm::vec3 mForward;
	glm::vec3 mSide;
	glm::vec3 mUp;
	glm::vec3 mFocusTar;

	bool mAlwaysFocus;
	float mSideSpeed;
	float mUpSpeed;
	float mForwadSpeed;
	float mFov;
};