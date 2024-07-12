#pragma once

#include <string>
#include "texture.h"
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <SDL2/SDL.h>
#include <vector>

Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{
}

Texture::~Texture()
{
}

void Texture::FlipVertical(unsigned char* image, int width, int height, int channels) {
	int rowSize = width * channels;
	std::vector<unsigned int> rowBuffer(rowSize);

	for (int i = 0; i < height / 2; ++i) {
		unsigned char* row_up = image + i * rowSize;
		unsigned char* row_down = image + (height - i - 1) * rowSize;

		std::copy(row_up, row_up + rowSize, rowBuffer.begin());
		std::copy(row_down, row_down + rowSize, row_up);
		std::copy(rowBuffer.begin(), rowBuffer.end(), row_down);
	}
}

bool Texture::Load(const std::string& fileName)
{
	int channels = 0;
	unsigned char* image = SOIL_load_image(fileName.c_str(),
		&mWidth, &mHeight, &channels, SOIL_LOAD_AUTO);

	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	FlipVertical(image, mWidth, mHeight, channels);

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0
		, format, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::CreateFromSurface(SDL_Surface* surface)
{
	mWidth = surface->w;
	mHeight = surface->h;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight
		, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

