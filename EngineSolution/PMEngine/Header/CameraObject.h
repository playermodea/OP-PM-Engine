#pragma once

#include <string>

#include "GameObject.h"

class CameraObject : public GameObject
{
public:
	CameraObject(std::string name = "DefaultCamera", std::string tag = "MainCamera") : GameObject(name, tag) {}
};