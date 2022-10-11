#include "MeshRendererComponent.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

MeshRendererComponent::MeshRendererComponent(Mesh* mesh, Texture* texture, Shader* shader) : CurMesh(mesh), CurTexture(texture), CurShader(shader)
{
	CompType = "Renderer";
	Awake();
}

MeshRendererComponent::~MeshRendererComponent()
{
	delete CurMesh;
	delete CurTexture;
	delete CurShader;
}

void MeshRendererComponent::Awake()
{
	//cout << "MeshRendererComponent 컴포넌트 Awake호출!" << endl;
}

void MeshRendererComponent::Start()
{
	//cout << "MeshRendererComponent 컴포넌트 Start호출!" << endl;
}

void MeshRendererComponent::FixedUpdate()
{
	//cout << "MeshRendererComponent 컴포넌트 FixedUpdate 호출!" << endl;
	//CurMat->GetTexture("diffuse")->Bind();
}

void MeshRendererComponent::Update()
{
	//cout << "MeshRendererComponent 컴포넌트 Update 호출!" << endl;
}

void MeshRendererComponent::LateUpdate()
{
	//cout << "MeshRendererComponent 컴포넌트 LateUpdate 호출!" << endl;
}

void MeshRendererComponent::Render()
{
	//cout << "MeshRendererComponent 컴포넌트 Render 호출!" << endl;

	if (CurShader)
	{
		CurShader->Use();
	}
	if (CurTexture)
	{
		CurTexture->BindTexture();
	}
	if (CurMesh)
	{
		CurMesh->Draw();
	}
	if (CurTexture)
	{
		CurTexture->UnBindTexture();
	}
	if (CurShader)
	{
		CurShader->Stop();
	}

}