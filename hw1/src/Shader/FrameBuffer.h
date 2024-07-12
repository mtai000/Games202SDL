#pragma once

class FrameBuffer {
public:
	FrameBuffer();
	FrameBuffer(unsigned int widht, unsigned int height);
	~FrameBuffer();

	unsigned int id;
	unsigned int colorAttachment;
	unsigned int depthAttachment;

	void Active();
	void Disactive();

	void deleteBuffer(bool isDelete = false);

};