#include "TestToolComponent.h"
#include "InputManager.h"
#include "GameObject.h"
#include "SoundManager.h"

void TestToolComponent::Update()
{
	KeyboardInput();
}

void TestToolComponent::KeyboardInput()
{
	glm::vec3 parentPos = ParentGO->GetTransform()->GetWorldPos();
	glm::vec3 parentRot = ParentGO->GetTransform()->GetWorldRot();

	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_UP))
	{
		ParentGO->GetTransform()->SetWorldPos(glm::vec3(parentPos.x, parentPos.y, parentPos.z - 0.1f));
	}
	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		ParentGO->GetTransform()->SetWorldPos(glm::vec3(parentPos.x, parentPos.y, parentPos.z + 0.1f));
	}
	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		ParentGO->GetTransform()->SetWorldPos(glm::vec3(parentPos.x + 0.1f, parentPos.y, parentPos.z));
	}
	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		ParentGO->GetTransform()->SetWorldPos(glm::vec3(parentPos.x - 0.1f, parentPos.y, parentPos.z));
	}
	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_Q))
	{
		ParentGO->GetTransform()->SetWorldRot(glm::vec3(parentRot.x, parentRot.y - 0.1f, parentRot.z));
	}
	if (InputManager::Instance()->IsKeyDown(SDL_SCANCODE_E))
	{
		ParentGO->GetTransform()->SetWorldRot(glm::vec3(parentRot.x, parentRot.y + 0.1f, parentRot.z));
	}
	if (InputManager::Instance()->IsKeyOneDown(SDL_SCANCODE_F))
	{
		SoundManager::Instance()->FindSound("../../Resources/Sound/Music.mp3");
		SoundManager::Instance()->Play();
	}
	if (InputManager::Instance()->IsKeyOneDown(SDL_SCANCODE_G))
	{
		SoundManager::Instance()->FindSound("../../Resources/Sound/Music.mp3");
		SoundManager::Instance()->Pause();
	}
}