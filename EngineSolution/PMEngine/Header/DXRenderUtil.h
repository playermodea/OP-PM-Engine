#pragma once

#include "RenderUtil.h"

class DXRenderUtil : public RenderUtil
{
public:
	virtual void Init() override {}
	virtual void InitLight() override {}
	virtual void StartScreen() override {};
	virtual void EndScreen() override {};
	virtual void ObjectRenderStart(TransformComponent* transform) override {}
	virtual void ObjectRenderEnd() override {}
	virtual void MainCamView() override {}
	virtual void Reshape(int width, int height) override {}
	virtual void PerspectiveProjection() override {}
	virtual void OrthoProjection() override {}
	virtual void UpdateMatrix(TransformComponent* transform) override {}
};

// DX 구현하면 쓸려고 미리 만들어 둔 코드, 아직 작동 X