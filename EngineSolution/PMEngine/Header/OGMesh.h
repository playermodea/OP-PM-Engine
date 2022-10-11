#pragma once

#include <string>

#include "Mesh.h"

class Shader;

class OGMesh : public Mesh
{
public:
	OGMesh() {}
	OGMesh(std::string const &path);
	~OGMesh() {}

	virtual void Draw() override;
	virtual void LoadMesh(const std::string &path) override;
	virtual void InitMesh() override;
};