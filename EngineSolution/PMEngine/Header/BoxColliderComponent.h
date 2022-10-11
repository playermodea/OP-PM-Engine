#pragma once

#include "ColliderComponent.h"
#include "glm/glm.hpp"

class BoxColliderComponent : public ColliderComponent
{
public:
	BoxColliderComponent();

	virtual void Start() override;
	virtual void Update() override;
	virtual bool GetCollision(ColliderComponent* coll) override;

public:
	bool GetSeparatingPlane(const glm::vec3& RPos, const glm::vec3& Plane, ColliderComponent* coll);
	void UpdateOrientation();
};