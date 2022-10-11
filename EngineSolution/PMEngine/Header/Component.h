#pragma once

#include <string>

#include "PMComponent.h"

class GameObject;

class Component :public PMComponent
{
protected:
	std::string CompType;
	GameObject* ParentGO;

public:
	Component();
	virtual ~Component() = 0 {}

	virtual void Awake() {}
	virtual void Start() {}
	virtual void FixedUpdate() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void Render() {}
	virtual void OnCollision() {}

public:
	// Setter
	void SetParentGO(GameObject* gameObj)
	{
		ParentGO = gameObj;
	}
	void settype(const std::string& a)
	{
		CompType = a;
	}

	// Getter
	std::string GetCompType()
	{
		return CompType;
	}
	GameObject* GetParentGO() const
	{ 
		return ParentGO; 
	}
};