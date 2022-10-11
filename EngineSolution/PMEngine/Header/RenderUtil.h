#pragma once

#include <vector>

#include "GameObject.h"
#include "CameraObject.h"
#include "OGShader.h"

class TransformComponent;

class RenderUtil
{
private:
	static RenderUtil* CurRenderUtil;
	static GameObject* MainCamera;
	static Shader* DefaultShader;

public:
	RenderUtil() {}
	virtual ~RenderUtil()
	{
		delete CurRenderUtil;
		delete MainCamera;
		delete DefaultShader;
	}

	virtual void Init() = 0;
	virtual void InitLight() = 0;
	virtual void StartScreen() = 0;
	virtual void EndScreen() = 0;
	virtual void ObjectRenderStart(TransformComponent* transform) = 0;
	virtual void ObjectRenderEnd() = 0;
	virtual void MainCamView() = 0;
	virtual void Reshape(int width, int height) = 0;
	virtual void PerspectiveProjection() = 0;
	virtual void OrthoProjection() = 0;
	virtual void UpdateMatrix(TransformComponent* transform) = 0;

public:
	// setter
	template<class renderUtil>
	static void SetRenderUtil()
	{ 
		CurRenderUtil = new renderUtil();
	}
	template<class shader>
	static void SetDefaultShader()
	{ 
		DefaultShader = new shader("default.vs", "default.fs");
	}
	static void SetMainCamera(std::vector<GameObject*> gameObjVec)
	{
		for (std::vector<GameObject*>::iterator iter = gameObjVec.begin(); iter != gameObjVec.end(); iter++)
		{
			GameObject* gameObj = *iter;

			if (gameObj->GetTag() == "MainCamera")
			{
				MainCamera = gameObj;

				return;
			}
		}

		MainCamera = new CameraObject("DefaultCamera", "MainCamera");
	}

	// getter
	static RenderUtil* GetRenderUtil()
	{ 
		return CurRenderUtil;
	}
	static Shader* GetDefaultShader()
	{ 
		return DefaultShader;
	}
	static GameObject* GetMainCamera()
	{ 
		return MainCamera;
	}
};