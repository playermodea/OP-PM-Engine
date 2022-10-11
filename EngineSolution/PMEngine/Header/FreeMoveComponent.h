#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class FreeMoveComponent : public Component
{
private:
	glm::vec2 OldMousePosition;
	glm::vec2 MouseRotation;
	glm::vec2 MouseRotationRad;

public:
	FreeMoveComponent();

	virtual void Update() override;

public:
	void MouseMove();
	void KeyboardInput();
};