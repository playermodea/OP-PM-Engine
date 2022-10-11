#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "SDL/SDL.h"
#include "EnumClass.h"

class InputManager
{
private:
	const Uint8* Keystates;
	glm::vec2* MousePosition;
	std::vector<bool> MouseButtonStates;
	bool IsOneDown[283];

	static InputManager* SingleInstance;

private:
	InputManager();

public:
	~InputManager() {}
	static InputManager* Instance();

	void Update();

	// keyboard
	bool IsKeyDown(SDL_Scancode key);
	bool IsKeyOneDown(SDL_Scancode key);
	void OnKeyDown();
	void OnKeyUp();

	// mouse
	bool GetMouseButtonState(int buttonNumber);
	void OnMouseMove(SDL_Event event);
	void OnMouseButtonDown(SDL_Event event);
	void OnMouseButtonUp(SDL_Event event);
	glm::vec2* GetMousePosition();
};