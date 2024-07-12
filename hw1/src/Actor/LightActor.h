#pragma once
#include <Core/Actor.h>

#include <glm/glm.hpp>
class LightActor : public Actor {
public:
	LightActor(class Game* _game);
	LightActor(class Game* _game, glm::vec3 pos);
	~LightActor();

	void InitFrameBuffer(unsigned int width, unsigned int height);

	void SetIntensity(glm::vec3 _i) { mIntensity = _i; };
	glm::vec3 GetIntensity() const { return mIntensity; };

	void SetColor(glm::vec3 _c) { mColor = _c; };
	glm::vec3 GetColor() const { return mColor; };

	void ResetPosition(glm::vec3);

	void SetRotateSpeed(float _v);
private:
	class LightComponent* mLightComp;
	class MeshComponent* mMeshComp;
	class FrameBufferComponent* mFrameBufferComp;

	glm::vec3 mIntensity;
	glm::vec3 mColor;
};