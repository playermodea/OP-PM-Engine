#pragma once

#include <map>

class Texture
{
protected:
	std::string FileName;

	unsigned int TextureID;

public:
	virtual ~Texture() {}

	virtual void LoadTexture(const std::string& path) = 0;
	virtual void InitTexture() = 0;
	virtual void BindTexture() const = 0;
	virtual void UnBindTexture() const = 0;

public:
	std::string GetFileName()
	{ 
		return FileName;
	}
	unsigned int GetTextureID()
	{ 
		return TextureID;
	}
};