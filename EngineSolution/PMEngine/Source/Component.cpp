#include "Component.h"
#include "GameObject.h"

Component::Component()
{
	CompType = "Custom";
	ParentGO = nullptr;
}