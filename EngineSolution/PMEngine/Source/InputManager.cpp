#include "InputManager.h"
#include "GameCore.h"

InputManager* InputManager::SingleInstance = 0;

InputManager* InputManager::Instance()
{
	if (SingleInstance == 0)
	{
		SingleInstance = new InputManager();
	}

	return SingleInstance;
}

InputManager::InputManager()
{
	MousePosition = new glm::vec2(0, 0);
	for (int i = 0; i < 3; i++)
	{
		MouseButtonStates.push_back(false);
	}
}

void InputManager::Update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			GameCore::Instance()->StopEngine();
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp(event);
			break;
		case SDL_KEYDOWN:
			OnKeyDown();
			break;
		case SDL_KEYUP:
			OnKeyUp();
			break;
		default:
			break;
		}
	}
}

bool InputManager::IsKeyDown(SDL_Scancode key)
{
	if (Keystates != 0)
	{
		if (Keystates[key] == 1)
		{
			return true;
		}
		else
		{ 
			return false;
		}
	}

	return false;
}

bool InputManager::IsKeyOneDown(SDL_Scancode key)
{
	if (Keystates != 0)
	{
		if (Keystates[key] == 1)
		{
			if (IsOneDown[key] == true)
			{
				return false;
			}

			IsOneDown[key] = true;
			return true;
		}
		else
		{
			IsOneDown[key] = false;
			return false;
		}
	}

	return false;
}

bool InputManager::GetMouseButtonState(int buttonNumber)
{
	return MouseButtonStates[buttonNumber];
}

glm::vec2* InputManager::GetMousePosition()
{
	return MousePosition;
}

void InputManager::OnMouseMove(SDL_Event event)
{
	MousePosition->x = event.motion.x;
	MousePosition->y = event.motion.y;
}

void InputManager::OnMouseButtonDown(SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		MouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		MouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		MouseButtonStates[RIGHT] = true;
	}
}

void InputManager::OnMouseButtonUp(SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		MouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		MouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		MouseButtonStates[RIGHT] = false;
	}
}

void InputManager::OnKeyDown()
{
	Keystates = SDL_GetKeyboardState(0);
}

void InputManager::OnKeyUp()
{
	Keystates = SDL_GetKeyboardState(0);
}