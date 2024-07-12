#pragma once
#include "Core/Component.h"

class FrameBufferComponent : public Component {
public:
	FrameBufferComponent(class Actor* owner, unsigned int width, unsigned int height);
	~FrameBufferComponent();

	void Active();
	void Disactive();

	unsigned int GetID() const { return mID; }
	unsigned int GetColorTexture() const { return mColorTexture; }
	unsigned int GetDepthTexture() const { return mDepthTexture; }

private:
	unsigned int mID;
	unsigned int mColorTexture;
	unsigned int mDepthTexture;

	void deleteBuffer(bool isDelete = false);
};