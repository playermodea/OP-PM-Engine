#include "OGFactory.h"
#include "OGMesh.h"
#include "OGTexture.h"
#include "OGShader.h"
#include "MeshRendererComponent.h"

MeshRendererComponent* OGFactory::CreateMesh(const std::string& meshPath
										   , const std::string& texturePath
										   , const char* vsPath
										   , const char* fsPath
										   , const char* gePath)
{
	if (vsPath && fsPath)
	{
		return new MeshRendererComponent(new OGMesh(meshPath), new OGTexture(texturePath), new OGShader(vsPath, fsPath, gePath));
	}

	return new MeshRendererComponent(new OGMesh(meshPath), new OGTexture(texturePath));
}

MeshRendererComponent* OGFactory::CreateCubeMesh()
{
	return new MeshRendererComponent(new OGMesh("../../Resources/Obj/cube.obj"), new OGTexture("../../Resources/Texture/default.png"));
}

MeshRendererComponent* OGFactory::CreatePlaneMesh()
{
	return new MeshRendererComponent(new OGMesh("../../Resources/Obj/plane.obj"), new OGTexture("../../Resources/Texture/default.png"));
}

MeshRendererComponent* OGFactory::CreateCylinderMesh()
{
	return new MeshRendererComponent(new OGMesh("../../Resources/Obj/cylinder.obj"), new OGTexture("../../Resources/Texture/default.png"));
}

MeshRendererComponent* OGFactory::CreateSphereMesh()
{
	return new MeshRendererComponent(new OGMesh("../../Resources/Obj/sphere.obj"), new OGTexture("../../Resources/Texture/default.png"));
}