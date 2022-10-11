#include "Project.h"
#include "OGFactory.h"
#include "DXFactory.h"
#include "InputManager.h"

Project::~Project()
{
	for (std::vector<Scene*>::iterator iter = SceneArray.begin(); iter != SceneArray.end(); iter++)
	{
		delete *iter;
	}

	SceneArray.clear();
}

void Project::ProjectInit(GraphicAPI mode)
{
	switch (mode)
	{
	case GraphicAPI::OpenGL:
		RendererFactory::SetRenderer<OGFactory>();
		break;
	case GraphicAPI::DirectX:
		RendererFactory::SetRenderer<DXFactory>();
		break;
	default:
		break;
	}

	CurScene = 0;
}

void Project::ProjectLoop(double perFrame)
{
	if (InputManager::Instance()->IsKeyOneDown(SDL_SCANCODE_2))
	{
		NextScene();
	}
	else if (InputManager::Instance()->IsKeyOneDown(SDL_SCANCODE_1))
	{
		PreviousScene();
	}

	if (SceneArray[CurScene]->GetIsStart())
	{
		SceneArray[CurScene]->Start();
		SceneArray[CurScene]->SetIsStart(false);
	}

	SceneArray[CurScene]->SceneLoop(perFrame);
}

void Project::AddScene(Scene* scene)
{
	SceneArray.push_back(scene);
}

void Project::NextScene()
{
	if (SceneArray.size() > CurScene + 1)
	{
		SceneArray[CurScene]->SetIsStart(true);
		CurScene++;
	}
}

void Project::PreviousScene()
{
	if (CurScene - 1 >= 0)
	{
		SceneArray[CurScene]->SetIsStart(true);
		CurScene--;
	}
}