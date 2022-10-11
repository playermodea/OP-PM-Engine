#pragma once

#include "Component.h"

class Mesh;
class Texture;
class Shader;

class MeshRendererComponent : public Component
{
private:
	Mesh* CurMesh;
	Texture* CurTexture;
	Shader* CurShader;

public:
	MeshRendererComponent(Mesh* mesh = nullptr, Texture* texture = nullptr, Shader* shader = nullptr);
	virtual ~MeshRendererComponent();

	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

public:
	void SetMesh(Mesh* mesh)
	{
		CurMesh = mesh;
	}
	void SetTexture(Texture* texture)
	{
		CurTexture = texture;
	}
	void SetShader(Shader* shader)
	{
		CurShader = shader;
	}
};
