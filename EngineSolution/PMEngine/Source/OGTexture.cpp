#include <iostream>
#include <string>

#include "OGTexture.h"
#include "ResourceManager.h"
#include "stb/stb_image.h"
#include "glew/glew.h"

OGTexture::OGTexture(const std::string& path)
{
	glGenTextures(1, &TextureID);

	LoadTexture(path);
}

OGTexture::~OGTexture()
{
	if (TextureID)
	{
		glDeleteTextures(1, &TextureID);
	}
}

void OGTexture::LoadTexture(const std::string& path)
{
	FileName = path;

	if (ResourceManager::Instance()->CheckTextureData(path))
	{
		std::cout << "The image already exists" << path << std::endl;
		TextureID = ResourceManager::Instance()->CheckTextureData(path)->GetTextureID();

		return;
	}
	else
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load((path).c_str(), &width, &height, &nrChannels, 4);
		if (data == NULL)
		{
			std::cout << "Failed to load texture: " << path << std::endl;
			return;
		}

		if (width > 0 && height > 0 && data != 0)
		{
			glBindTexture(GL_TEXTURE_2D, TextureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		ResourceManager::Instance()->InsertTextureData(path, this);

		stbi_image_free(data);
	}
}

void OGTexture::BindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, TextureID);
}

void OGTexture::UnBindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}