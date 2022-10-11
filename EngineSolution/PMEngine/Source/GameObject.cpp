#include <iostream>
#include <string>

#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderUtil.h"

GameObject::GameObject(std::string name, std::string tag) : Name(name), Tag(tag)
{
	IsCollision = false;
	Name = name;
	Parent = nullptr;
	Transform = new TransformComponent();
	AddComponent(Transform);

	Awake();
}

GameObject::~GameObject()
{
	for (std::vector<Component*>::iterator iter = ComponentArray.begin(); iter != ComponentArray.end(); iter++)
	{
		delete *iter;
	}

	ComponentArray.clear();

	for (std::vector<GameObject*>::iterator iter = ChildArray.begin(); iter != ChildArray.end(); iter++)
	{
		delete *iter;
	}

	ChildArray.clear();
}

void GameObject::Awake()
{

}

void GameObject::Start()
{
	for (std::vector<Component*>::iterator iter = ComponentArray.begin(); iter != ComponentArray.end(); iter++)
	{
		Component* Comp = *iter;
		Comp->Start();
	}
}

void GameObject::FixedUpdate()
{
	for (std::vector<Component*>::iterator iter = ComponentArray.begin(); iter != ComponentArray.end(); iter++)
	{
		Component* Comp = *iter;
		Comp->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (std::vector<Component*>::iterator iter = ComponentArray.begin(); iter != ComponentArray.end(); iter++)
	{
		Component* Comp = *iter;
		Comp->Update();
	}
}

void GameObject::LateUpdate()
{
	for (std::vector<Component*>::iterator iter = ComponentArray.begin(); iter != ComponentArray.end(); iter++)
	{
		Component* Comp = *iter;
		Comp->LateUpdate();
	}
}

void GameObject::Render()
{
	RenderUtil::GetRenderUtil()->ObjectRenderStart(Transform);
	for (std::vector<Component*>::iterator iter = ComponentArray.begin(); iter != ComponentArray.end(); iter++)
	{
		Component* Comp = *iter;
		Comp->Render();
	}
	RenderUtil::GetRenderUtil()->ObjectRenderEnd();
}

void GameObject::OnCollision()
{
	if (IsCollision)
	{
		std::cout << Name << " Collision 발생!" << std::endl;
		for (std::vector<Component*>::iterator iter = ComponentArray.begin(); iter != ComponentArray.end(); iter++)
		{
			Component* Comp = *iter;
			Comp->OnCollision();
		}
	}
}

void GameObject::AddComponent(Component* comp)
{
	ComponentArray.push_back(comp);

	comp->SetParentGO(this);
}

void GameObject::AddChild(GameObject* gameObj)
{
	ChildArray.push_back(gameObj);

	gameObj->SetParent(this);
	gameObj->GetTransform()->SetChildTransform(this->Transform);
}