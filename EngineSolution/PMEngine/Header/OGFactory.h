#pragma once

#include "RendererFactory.h"

class OGFactory : public RendererFactory
{
public:
	OGFactory() {}
	~OGFactory() {}

	virtual MeshRendererComponent* CreateMesh(const std::string& meshPath
											, const std::string& texturePath
											, const char* vsPath = nullptr
											, const char* fsPath = nullptr
											, const char* gePath = nullptr) override;
	virtual MeshRendererComponent* CreateCubeMesh() override;
	virtual MeshRendererComponent* CreatePlaneMesh() override;
	virtual MeshRendererComponent* CreateCylinderMesh() override;
	virtual MeshRendererComponent* CreateSphereMesh() override;
};