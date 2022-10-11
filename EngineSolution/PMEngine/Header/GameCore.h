#pragma once

#include <Windows.h>
#include <string>

#include "EnumClass.h"

class Project;

class GameCore
{
private:
	int Width;
	int	Height;
	bool IsRunning;
	std::string Title;
	GraphicAPI Mode;

	double PerFrame;
	double DeltaTime;
	LARGE_INTEGER FrameInfo;
	LARGE_INTEGER NowFrameCounter;
	LARGE_INTEGER PrevFrameCounter;

	Project* CurProject;

	static GameCore* SingleInstance;

private:
	GameCore();

public:
	~GameCore();
	static GameCore* Instance();

	void Init(const std::string& title = "PMEngine", int width = 700, int height = 700, Project* proj = nullptr, GraphicAPI mode = GraphicAPI::OpenGL);
	void SetProject(Project* proj);
	void StartEngine();
	void StopEngine();
	void EngineLoop();
	void UpdateDeltaTime();

	double GetDeltaTime()
	{
		return DeltaTime;
	}
};