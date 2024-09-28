#pragma once
#include <Core/Actor.h>
#include "head.h"
class LightActor : public Actor {
public:
	LightActor(class Game* _game, glm::vec3 pos);
	~LightActor();

	void InitFrameBuffer(unsigned int width, unsigned int height);
	void ResetPosition(glm::vec3);
	void SetRotateSpeed(float _v);
	class LightComponent* GetLightComponent();
private:
    class LightComponent* mLightComp;
	class MeshComponent* mMeshComp;
	class FrameBufferComponent* mFrameBufferComp;
};