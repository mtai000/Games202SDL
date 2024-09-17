#include "head.h"
#include "FrameBufferComponent.h"
#include "Core/Actor.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Core/Game.h"
#include "Core/Renderer.h"
#include "Core/Actor.h"
#include "Core/Component.h"

FrameBufferComponent::FrameBufferComponent(Actor* owner, unsigned int width, unsigned int height)
	:Component(owner)
{
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	mID = fbo;
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	unsigned int color_texture;
	glGenTextures(1, &color_texture);
	mColorTexture = color_texture;
	glBindTexture(GL_TEXTURE_2D, color_texture);

	//color����
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//�������Ʒ�ʽ
	//GL_REPEAT 	��������Ĭ����Ϊ���ظ�����ͼ��
	//GL_MIRRORED_REPEAT 	��GL_REPEATһ������ÿ���ظ�ͼƬ�Ǿ�����õġ�
	//GL_CLAMP_TO_EDGE 	��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
	//GL_CLAMP_TO_BORDER 	����������Ϊ�û�ָ���ı�Ե��ɫ��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture, 0);
	//�������ѡ��GL_CLAMP_TO_BORDERѡ���Ҫָ��һ����Ե����ɫ
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// �������
	unsigned int depth_texture;
	glGenTextures(1, &depth_texture);
	mDepthTexture = depth_texture;
	glBindTexture(GL_TEXTURE_2D, depth_texture);
	// �������������ֵ
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//�������Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		SDL_Log("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, NULL);

	GetOwner()->GetGame()->GetRenderer()->AddFrameBufferComp(this);
}

FrameBufferComponent::~FrameBufferComponent()
{
	GetOwner()->GetGame()->GetRenderer()->RemoveFrameBufferComp(this);
}

void FrameBufferComponent::Active()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mID);
}

void FrameBufferComponent::Disactive()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferComponent::deleteBuffer(bool isDelete)
{
	if (isDelete) {
		glDeleteTextures(1, &mColorTexture);
		glDeleteTextures(1, &mDepthTexture);
	}
	glDeleteFramebuffers(1, &mID);
}
