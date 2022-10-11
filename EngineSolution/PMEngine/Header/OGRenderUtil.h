#pragma once

#include "RenderUtil.h"

class OGRenderUtil : public RenderUtil
{
public:
	~OGRenderUtil() {}

	virtual void Init() override;
	virtual void InitLight() override;
	virtual void StartScreen() override;
	virtual void EndScreen() override;
	virtual void ObjectRenderStart(TransformComponent* transform) override;
	virtual void ObjectRenderEnd() override;
	virtual void MainCamView() override;
	virtual void Reshape(int width, int height) override;
	virtual void PerspectiveProjection() override;
	virtual void OrthoProjection() override;
	virtual void UpdateMatrix(TransformComponent* transform) override;
};