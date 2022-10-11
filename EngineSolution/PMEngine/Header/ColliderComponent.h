#pragma once

#include "Component.h"
#include "GameObject.h"

class ColliderComponent : public Component
{
protected:
	float AxisLen[3];
	bool IsCollision;
	glm::vec3 BoxCenterPos;
	glm::vec3 AxisDir[3];

public:
	ColliderComponent()
	{
		CompType = "Collider";
	}
	virtual ~ColliderComponent() {};

	virtual bool GetCollision(ColliderComponent* coll) = 0;

public:
	// setter
	void SetCollisionState(bool value)
	{
		IsCollision = value;
		ParentGO->SetCollision(value);
	}
	void SetScale(glm::vec3 scale)
	{
		AxisLen[0] = scale.x;
		AxisLen[1] = scale.y;
		AxisLen[2] = scale.z;
	}

	// getter
	glm::vec3 GetBoxCenter()
	{
		return BoxCenterPos;
	}
	glm::vec3* GetAxisDir()
	{
		return AxisDir;
	}
	float* GetAxisLen()
	{
		return AxisLen;
	}
};