#pragma once

#include <vector>

#include "Vertex.h"

class Shader;

class Mesh
{
protected:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	bool TextCoordState;

	std::string FileName;
	std::vector<Vertex> MeshData;
	std::vector<int> Indices;

public:
	virtual ~Mesh() {}
	
	virtual void Draw() = 0;
	virtual void LoadMesh(const std::string &path) = 0;
	virtual void InitMesh() = 0;

public:
	std::string GetFileName() const 
	{ 
		return FileName; 
	}
	std::vector<Vertex> GetMeshData() const 
	{ 
		return MeshData;
	}
	std::vector<int> GetIndicesData() const 
	{ 
		return Indices; 
	}
	unsigned int GetVAO() const 
	{ 
		return VAO;
	}
	unsigned int GetVBO() const 
	{ 
		return VBO;
	}
	unsigned int GetEBO() const 
	{ 
		return EBO; 
	}
};