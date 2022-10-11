#pragma once

#include <vector>

#include "PMGameObject.h"
#include "TransformComponent.h"
#include "glm/glm.hpp"

class GameObject : public PMGameObject
{
protected:
	bool IsCollision;
	std::string Name;
	std::string Tag;

	GameObject* Parent;
	TransformComponent* Transform;

	std::vector<Component*> ComponentArray;
	std::vector<GameObject*> ChildArray;

public:
	GameObject(std::string name = "DefaultName", std::string tag = "DefaultTag");
	virtual ~GameObject() = 0;

	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void OnCollision() override;

public:
	void AddComponent(Component* comp);
	void AddChild(GameObject* gameObj);

	// setter
	void SetName(const std::string& name)
	{
		Name = name;
	}
	void SetTag(const std::string& tag)
	{
		Tag = tag;
	}
	void SetParent(GameObject* parentObj)
	{
		Parent = parentObj;
	}
	void SetCollision(bool value)
	{
		IsCollision = value;
	}

	// getter
	std::string GetName() const
	{
		return Name;
	}
	std::string GetTag() const
	{ 
		return Tag; 
	}
	GameObject* GetParent() const 
	{ 
		return Parent; 
	}
	TransformComponent* GetTransform() const 
	{ 
		return Transform;
	}
	std::vector<Component*> GetCompArray() const 
	{ 
		return ComponentArray;
	}
};