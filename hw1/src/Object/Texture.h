#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	void FlipVertical(unsigned char* image, int widht, int height, int channels);

    unsigned char floatToByte(float value);

    bool Load(const std::string& fileName);
	void Unload();
	void CreateFromSurface(struct SDL_Surface* surface);

	void SetActive();

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	std::string GetTexturePath() const { return mTexturePath; }
	unsigned int GetTextureID() { 
		return mTextureID; 
	}
private:
	unsigned int mTextureID;
	std::string mTexturePath;
	int mWidth;
	int mHeight;

	std::string type;
	std::string path;
};