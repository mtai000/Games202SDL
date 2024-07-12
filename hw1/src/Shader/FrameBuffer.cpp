#include "FrameBuffer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "SDL2/SDL.h"

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	id = fbo;
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	unsigned int color_texture;
	glGenTextures(1, &color_texture);
	colorAttachment = color_texture;
	glBindTexture(GL_TEXTURE_2D, color_texture);

	//color纹理
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//纹理环绕方式
	//GL_REPEAT 	对纹理的默认行为。重复纹理图像。
	//GL_MIRRORED_REPEAT 	和GL_REPEAT一样，但每次重复图片是镜像放置的。
	//GL_CLAMP_TO_EDGE 	纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
	//GL_CLAMP_TO_BORDER 	超出的坐标为用户指定的边缘颜色。
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture, 0);
	//如果我们选择GL_CLAMP_TO_BORDER选项，需要指定一个边缘的颜色
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// 深度纹理
	unsigned int depth_texture;
	glGenTextures(1, &depth_texture);
	depthAttachment = depth_texture;
	glBindTexture(GL_TEXTURE_2D, depth_texture);
	// 给深度纹理对象赋值
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//纹理环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		SDL_Log("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::Active()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FrameBuffer::Disactive()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::deleteBuffer(bool isDelete)
{
	if (isDelete) {
		glDeleteTextures(1, &colorAttachment);
		glDeleteTextures(1, &depthAttachment);
	}
	glDeleteFramebuffers(1, &id);
}
