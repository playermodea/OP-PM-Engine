#pragma once

#include <vector>

#include "Scene.h"
#include "EnumClass.h"

class RendererFactory;

class Project
{
private:
	int CurScene;

	std::vector<Scene*> SceneArray;

public:
	Project() {};
	virtual ~Project();

	virtual void ProjectInit(GraphicAPI mode = GraphicAPI::OpenGL);

public:
	void ProjectLoop(double perFrame);
	void AddScene(Scene* scene);
	void NextScene();
	void PreviousScene();
};