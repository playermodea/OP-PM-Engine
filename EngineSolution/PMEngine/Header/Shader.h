﻿#pragma once

#include <string>

#include "glm/glm.hpp"

class Shader
{
private:
	virtual void CheckCompileErrors(unsigned int shader, std::string type) = 0;

protected:
	unsigned int ID;

public:
	virtual ~Shader() {}

	virtual void LoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) = 0;
	virtual void Use() = 0;
	virtual void Stop() = 0;
	virtual void SetBool(const std::string &name, bool value) const = 0;
	virtual void SetInt(const std::string &name, int value) const = 0;
	virtual void SetFloat(const std::string &name, float value) const = 0;
	virtual void SetVec2(const std::string &name, const glm::vec2 &value) const = 0;
	virtual void SetVec2(const std::string &name, float x, float y) const = 0;
	virtual void SetVec3(const std::string &name, const glm::vec3 &value) const = 0;
	virtual void SetVec3(const std::string &name, float x, float y, float z) const = 0;
	virtual void SetVec4(const std::string &name, const glm::vec4 &value) const = 0;
	virtual void SetVec4(const std::string &name, float x, float y, float z, float w) = 0;
	virtual void SetMat2(const std::string &name, const glm::mat2 &mat) const = 0;
	virtual void SetMat3(const std::string &name, const glm::mat3 &mat) const = 0;
	virtual void SetMat4(const std::string &name, const glm::mat4 &mat) const = 0;

public:
	unsigned int GetShaderID()
	{ 
		return ID;
	}
};
