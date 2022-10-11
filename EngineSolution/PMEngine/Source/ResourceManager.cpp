#include "ResourceManager.h"

ResourceManager* ResourceManager::SingleInstance = 0;

ResourceManager* ResourceManager::Instance()
{
	if (SingleInstance == 0)
	{
		SingleInstance = new ResourceManager();
	}

	return SingleInstance;
}

ResourceManager::~ResourceManager()
{
	ClearTextureData();
	ClearMeshData();
	ClearShaderData();
	ClearSoundData();
}

Texture* ResourceManager::CheckTextureData(const std::string& path)
{
	std::map<std::string, Texture*>::const_iterator it = TextureMap.find(path);
	if (it != TextureMap.end())
	{
		return it->second;
	}

	return false;
}

Mesh* ResourceManager::CheckMeshData(const std::string& path)
{
	std::map<std::string, Mesh*>::const_iterator it = MeshMap.find(path);
	if (it != MeshMap.end())
	{
		return it->second;
	}

	return false;
}

Shader* ResourceManager::CheckShaderData(const char* path)
{
	std::map<const char*, Shader*>::const_iterator it = ShaderMap.find(path);
	if (it != ShaderMap.end())
	{
		return it->second;
	}

	return false;
}

Sound* ResourceManager::CheckSoundData(const char* path)
{
	std::map<const char*, Sound*>::const_iterator it = SoundMap.find(path);
	if (it != SoundMap.end())
	{
		return it->second;
	}

	return false;
}

void ResourceManager::InsertTextureData(const std::string& path, Texture* texture)
{
	TextureMap.insert(std::pair<std::string, Texture*>(path, texture));
}

void ResourceManager::InsertMeshData(const std::string& path, Mesh* mesh)
{
	MeshMap.insert(std::pair<std::string, Mesh*>(path, mesh));
}

void ResourceManager::InsertShaderData(const char* path, Shader* shader)
{
	ShaderMap.insert(std::pair<const char*, Shader*>(path, shader));
}

void ResourceManager::InsertSoundData(const char* path, Sound* sound)
{
	SoundMap.insert(std::pair<const char*, Sound*>(path, sound));
}

void ResourceManager::ClearTextureData()
{
	for (std::map<std::string, Texture*>::iterator iter = TextureMap.begin(); iter != TextureMap.end(); iter++)
	{
		delete iter->second;
	}

	TextureMap.clear();
}
void ResourceManager::ClearMeshData()
{
	for (std::map<std::string, Mesh*>::iterator iter = MeshMap.begin(); iter != MeshMap.end(); iter++)
	{
		delete iter->second;
	}

	MeshMap.clear();
}

void ResourceManager::ClearShaderData()
{
	for (std::map<const char*, Shader*>::iterator iter = ShaderMap.begin(); iter != ShaderMap.end(); iter++)
	{
		delete iter->second;
	}

	ShaderMap.clear();
}

void ResourceManager::ClearSoundData()
{
	for (std::map < const char*, Sound*>::iterator iter = SoundMap.begin(); iter != SoundMap.end(); iter++)
	{
		delete iter->second;
	}

	SoundMap.clear();
}