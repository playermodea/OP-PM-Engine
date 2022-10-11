#pragma once

#include <map>

#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Sound.h"

class ResourceManager
{
private:
	std::map<std::string, Texture*> TextureMap;
	std::map<std::string, Mesh*> MeshMap;
	std::map<const char*, Shader*> ShaderMap;
	std::map<const char*, Sound*> SoundMap;

	static ResourceManager* SingleInstance;

private:
	ResourceManager() {};

public:
	~ResourceManager();

	static ResourceManager* Instance();

	Texture* CheckTextureData(const std::string& path);
	Mesh* CheckMeshData(const std::string& path);
	Shader* CheckShaderData(const char* path);
	Sound* CheckSoundData(const char* path);

	void InsertTextureData(const std::string& path, Texture* texture);
	void InsertMeshData(const std::string& path, Mesh* mesh);
	void InsertShaderData(const char* path, Shader* shader);
	void InsertSoundData(const char* path, Sound* sound);

	void ClearTextureData();
	void ClearMeshData();
	void ClearShaderData();
	void ClearSoundData();
};