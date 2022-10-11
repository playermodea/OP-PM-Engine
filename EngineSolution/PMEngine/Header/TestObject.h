#pragma once

#include "GameObject.h"

class TestObject : public GameObject
{
public:
	TestObject(std::string name, std::string tag) : GameObject(name, tag) {}
};