#include <iostream>

#include "GameCore.h"
#include "Project.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "RenderUtil.h"
#include "OGRenderUtil.h"
#include "DXRenderUtil.h"

GameCore* GameCore::SingleInstance = 0;

GameCore::GameCore()
{
	QueryPerformanceFrequency(&FrameInfo);
	QueryPerformanceCounter(&PrevFrameCounter);

	PerFrame = FrameInfo.QuadPart / 60.0f;
}

GameCore::~GameCore()
{
	delete CurProject;
}

GameCore* GameCore::Instance()
{
	if (SingleInstance == 0)
	{
		SingleInstance = new GameCore();
	}

	return SingleInstance;
}

void GameCore::Init(const std::string& title, int width, int height, Project* proj, GraphicAPI mode)
{
	Title = title;
	Width = width;
	Height = height;
	CurProject = proj;
	Mode = mode;

	switch (mode)
	{
	case GraphicAPI::OpenGL:
		RenderUtil::SetRenderUtil<OGRenderUtil>();
		break;
	case GraphicAPI::DirectX:
		RenderUtil::SetRenderUtil<DXRenderUtil>();
		break;
	default:
		break;
	}
}

void GameCore::SetProject(Project* proj)
{
	CurProject = proj;
}

void GameCore::StartEngine()
{
	if (IsRunning)
	{
		return;
	}

	EngineLoop();
}

void GameCore::StopEngine()
{
	if (!IsRunning)
	{
		return;
	}

	IsRunning = false;
}

void GameCore::EngineLoop()
{
	IsRunning = true;

	WindowManager::Instance()->InitSDL(Title, Width, Height);
	WindowManager::Instance()->CreateSDLWindow();
	SoundManager::Instance()->InitSound();
	RenderUtil::GetRenderUtil()->Init();

	CurProject->ProjectInit(Mode);

	WindowManager::Instance()->SetMouseCenter();
	while (IsRunning)
	{
		UpdateDeltaTime();
		InputManager::Instance()->Update();
		SoundManager::Instance()->Update();

		if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
		{
			StopEngine();
		}

		RenderUtil::GetRenderUtil()->StartScreen();;
		CurProject->ProjectLoop(PerFrame);
		RenderUtil::GetRenderUtil()->EndScreen();

		WindowManager::Instance()->SDLSwapBuffer();
	}

	SoundManager::Instance()->SoundEnd();
	WindowManager::Instance()->DestroySDLWindow();
}

void GameCore::UpdateDeltaTime()
{
	QueryPerformanceCounter(&NowFrameCounter);

	DeltaTime = (NowFrameCounter.QuadPart - PrevFrameCounter.QuadPart) / FrameInfo.QuadPart;

	PrevFrameCounter = NowFrameCounter;
}