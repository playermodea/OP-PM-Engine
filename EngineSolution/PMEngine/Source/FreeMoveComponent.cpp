#define _USE_MATH_DEFINES
#include <math.h>

#include "FreeMoveComponent.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

FreeMoveComponent::FreeMoveComponent()
{
	CompType = "Custom";
	OldMousePosition = glm::vec2(0.0f, 0.0f);
	MouseRotation = glm::vec2(0.0f, 0.0f);
	MouseRotationRad = glm::vec2(0.0f, 0.0f);
}

void FreeMoveComponent::Update()
{
	MouseMove();
	KeyboardInput();
}

void FreeMoveComponent::MouseMove()
{
	glm::vec3 parentRot = ParentGO->GetTransform()->GetWorldRot();

	glm::vec2 diffPos = glm::vec2(InputManager::Instance()->GetMousePosition()->x
								, InputManager::Instance()->GetMousePosition()->y) - OldMousePosition;

	OldMousePosition = glm::vec2(InputManager::Instance()->GetMousePosition()->x
							   , InputManager::Instance()->GetMousePosition()->y);

	MouseRotation += glm::vec2(diffPos.y, diffPos.x);

	ParentGO->GetTransform()->SetWorldRot(glm::vec3(MouseRotation.x, MouseRotation.y, parentRot.z));
}

void FreeMoveComponent::KeyboardInput()
{
	glm::vec3 parentPos = ParentGO->GetTransform()->GetWorldPos();
	MouseRotationRad = glm::vec2(MouseRotation.x / 180 * M_PI, MouseRotation.y / 180 * M_PI);

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_W))
	{
		ParentGO->GetTransform()->SetWorldPos(glm::vec3(parentPos.x + float(sin(MouseRotationRad.y)) / 10
													, parentPos.y - float(sin(MouseRotationRad.x)) / 10
													, parentPos.z - float(cos(MouseRotationRad.y)) / 10));
	}
	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_S))
	{
		ParentGO->GetTransform()->SetWorldPos(glm::vec3(parentPos.x - float(sin(MouseRotationRad.y)) / 10
													, parentPos.y + float(sin(MouseRotationRad.x)) / 10
													, parentPos.z + float(cos(MouseRotationRad.y)) / 10));
	}

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_A))
	{
		ParentGO->GetTransform()->SetWorldPos(glm::vec3(parentPos.x - float(cos(MouseRotationRad.y)) / 10
													, parentPos.y
													, parentPos.z - float(sin(MouseRotationRad.y)) / 10));
	}
	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_D))
	{
		ParentGO->GetTransform()->SetWorldPos(glm::vec3(parentPos.x + float(cos(MouseRotationRad.y)) / 10
													, parentPos.y
													, parentPos.z + float(sin(MouseRotationRad.y)) / 10));
	}
}