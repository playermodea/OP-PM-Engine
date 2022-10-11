#pragma once

#include "Shader.h"

class OGShader : public Shader
{
private:
	virtual void CheckCompileErrors(unsigned int shader, std::string type) override;

public:
	OGShader() {}
	OGShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	~OGShader() {}

	virtual void LoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) override;
	virtual void Use() override;
	virtual void Stop() override;
	virtual void SetBool(const std::string &name, bool value) const override;
	virtual void SetInt(const std::string &name, int value) const override;
	virtual void SetFloat(const std::string &name, float value) const override;
	virtual void SetVec2(const std::string &name, const glm::vec2 &value) const override;
	virtual void SetVec2(const std::string &name, float x, float y) const override;
	virtual void SetVec3(const std::string &name, const glm::vec3 &value) const override;
	virtual void SetVec3(const std::string &name, float x, float y, float z) const override;
	virtual void SetVec4(const std::string &name, const glm::vec4 &value) const override;
	virtual void SetVec4(const std::string &name, float x, float y, float z, float w) override;
	virtual void SetMat2(const std::string &name, const glm::mat2 &mat) const override;
	virtual void SetMat3(const std::string &name, const glm::mat3 &mat) const override;
	virtual void SetMat4(const std::string &name, const glm::mat4 &mat) const override;
};