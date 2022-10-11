#pragma once

#include <string>

#include "SDL/SDL.h"

class WindowManager
{
private:
	int Width;
	int	Height;
	std::string Title;

	SDL_Window* Window;
	SDL_GLContext GLContext;

	static WindowManager* SingleInstance;

private:
	WindowManager() {}

public:
	~WindowManager();
	static WindowManager* Instance();

	void InitSDL(const std::string& title, int width, int height);
	void CreateSDLWindow(bool fullscreen = false);
	void DestroySDLWindow();
	void SDLSwapBuffer();
	void SetFullScreen(bool value);
	void SetMouseCenter();

	int GetWidth() const
	{ 
		return Width;
	}
	int GetHeight() const
	{ 
		return Height;
	}
	float GetAspect() const
	{ 
		return float(Width / Height);
	}
	const std::string GetTitle() const
	{ 
		return Title;
	}
};