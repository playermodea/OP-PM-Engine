#pragma once

#include "RendererFactory.h"
#include "MeshRendererComponent.h"

class DXFactory : public RendererFactory
{
public:
	virtual MeshRendererComponent* CreateMesh(const std::string& meshPath
											, const std::string& texturePath
											, const char* vsPath = nullptr
											, const char* fsPath = nullptr
											, const char* gePath = nullptr) override
	{ 
		return new MeshRendererComponent();
	}
	virtual MeshRendererComponent* CreateCubeMesh() override
	{ 
		return new MeshRendererComponent();
	}
	virtual MeshRendererComponent* CreatePlaneMesh() override
	{ 
		return new MeshRendererComponent();
	}
	virtual MeshRendererComponent* CreateCylinderMesh() override
	{
		return new MeshRendererComponent();
	}
	virtual MeshRendererComponent* CreateSphereMesh() override
	{
		return new MeshRendererComponent();
	}
};

// DX 구현하면 쓸려고 미리 만들어 둔 코드, 아직 작동 X