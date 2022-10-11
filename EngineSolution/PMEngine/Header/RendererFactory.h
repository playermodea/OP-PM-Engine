#pragma once

#include <string>

class MeshRendererComponent;

class RendererFactory
{
private:
	static RendererFactory* CurFactory;

public:
	RendererFactory() {}
	virtual ~RendererFactory()
	{ 
		delete CurFactory; 
	}

	virtual MeshRendererComponent* CreateMesh(const std::string& meshPath
											, const std::string& texturePath
											, const char* vsPath = nullptr
											, const char* fsPath = nullptr
											, const char* gePath = nullptr) = 0;
	virtual MeshRendererComponent* CreateCubeMesh() = 0;
	virtual MeshRendererComponent* CreatePlaneMesh() = 0;
	virtual MeshRendererComponent* CreateCylinderMesh() = 0;
	virtual MeshRendererComponent* CreateSphereMesh() = 0;

public:
	// setter
	template<class renderFactory>
	static void SetRenderer()
	{ 
		CurFactory = new renderFactory();
	}

	// getter
	static RendererFactory* GetRenderer()
	{ 
		return CurFactory;
	}
};