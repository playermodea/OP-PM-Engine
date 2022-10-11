#pragma once

#include "Component.h"

class TestToolComponent : public Component
{
public:
	virtual void Update() override;

public:
	void KeyboardInput();
};