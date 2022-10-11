#include "WindowManager.h"
#include "glew/glew.h"

WindowManager* WindowManager::SingleInstance = 0;

WindowManager* WindowManager::Instance()
{
	if (SingleInstance == 0)
	{
		SingleInstance = new WindowManager();
	}

	return SingleInstance;
}

WindowManager::~WindowManager()
{
	delete Window;
}

void WindowManager::InitSDL(const std::string& title, int width, int height)
{
	Width = width;
	Height = height;
	Title = title;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void WindowManager::CreateSDLWindow(bool fullscreen)
{
	int mode = 0;

	if (fullscreen)
	{
		mode = SDL_WINDOW_FULLSCREEN;
	}

	Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_OPENGL | mode);
	GLContext = SDL_GL_CreateContext(Window);

	SDL_GL_SetSwapInterval(1);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}
}

void WindowManager::DestroySDLWindow()
{
	if (!Window)
	{
		return;
	}

	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void WindowManager::SDLSwapBuffer()
{
	SDL_GL_SwapWindow(Window);
}

void WindowManager::SetFullScreen(bool value)
{
	int mode = 0;

	if (value)
		mode = SDL_WINDOW_FULLSCREEN;
	else
		mode = 0;

	SDL_SetWindowFullscreen(Window, mode);
}

void WindowManager::SetMouseCenter()
{
	SDL_WarpMouseInWindow(Window, Width / 2, Height / 2);
}