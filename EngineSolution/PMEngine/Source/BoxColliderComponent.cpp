#define _USE_MATH_DEFINES
#include <math.h>

#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "glm/gtx/transform.hpp"

BoxColliderComponent::BoxColliderComponent()
{
	AxisDir[0] = glm::vec3(1.0f, 0.0f, 0.0f);
	AxisDir[1] = glm::vec3(0.0f, 1.0f, 0.0f);
	AxisDir[2] = glm::vec3(0.0f, 0.0f, 1.0f);
	AxisLen[0] = 1.0f;
	AxisLen[1] = 1.0f;
	AxisLen[2] = 1.0f;
	IsCollision = false;
}

void BoxColliderComponent::Start()
{
	BoxCenterPos = ParentGO->GetTransform()->GetWorldPos();
}

void BoxColliderComponent::Update()
{
	UpdateOrientation();
}

bool BoxColliderComponent::GetCollision(ColliderComponent* coll)
{
	static glm::vec3 RPos;
	RPos = coll->GetBoxCenter() - BoxCenterPos;

	return !(GetSeparatingPlane(RPos, AxisDir[0], coll) ||
		GetSeparatingPlane(RPos, AxisDir[1], coll) ||
		GetSeparatingPlane(RPos, AxisDir[2], coll) ||
		GetSeparatingPlane(RPos, coll->GetAxisDir()[0], coll) ||
		GetSeparatingPlane(RPos, coll->GetAxisDir()[1], coll) ||
		GetSeparatingPlane(RPos, coll->GetAxisDir()[2], coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[0], coll->GetAxisDir()[0]), coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[0], coll->GetAxisDir()[1]), coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[0], coll->GetAxisDir()[2]), coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[1], coll->GetAxisDir()[0]), coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[1], coll->GetAxisDir()[1]), coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[1], coll->GetAxisDir()[2]), coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[2], coll->GetAxisDir()[0]), coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[2], coll->GetAxisDir()[1]), coll) ||
		GetSeparatingPlane(RPos, glm::cross(AxisDir[2], coll->GetAxisDir()[2]), coll));
}

bool BoxColliderComponent::GetSeparatingPlane(const glm::vec3& RPos, const glm::vec3& Plane, ColliderComponent* coll)
{
	return (glm::length(glm::abs(RPos*Plane)) >
		glm::length(glm::abs((AxisDir[0] * AxisLen[0])*Plane) +
			glm::abs((AxisDir[1] * AxisLen[1])*Plane) +
			glm::abs((AxisDir[2] * AxisLen[2])*Plane) +
			glm::abs((coll->GetAxisDir()[0] * coll->GetAxisLen()[0])*Plane) +
			glm::abs((coll->GetAxisDir()[1] * coll->GetAxisLen()[1])*Plane) +
			glm::abs((coll->GetAxisDir()[2] * coll->GetAxisLen()[2])*Plane)));
}

void BoxColliderComponent::UpdateOrientation()
{
	glm::vec3 parentPos = ParentGO->GetTransform()->GetWorldPos();
	glm::vec3 parentRot = ParentGO->GetTransform()->GetWorldRot();

	BoxCenterPos = parentPos;

	glm::mat4 objMat = glm::rotate(glm::mat4(1.0f), glm::radians(parentRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	objMat *= glm::rotate(glm::mat4(1.0f), glm::radians(parentRot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	objMat *= glm::rotate(glm::mat4(1.0f), glm::radians(parentRot.y), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 inversted = glm::inverse(objMat);
	glm::vec3 right = glm::normalize(glm::vec3(inversted[0]));
	glm::vec3 up = glm::normalize(glm::vec3(inversted[1]));
	glm::vec3 forward = glm::normalize(glm::vec3(inversted[2]));

	AxisDir[0] = right;
	AxisDir[1] = up;
	AxisDir[2] = forward;
}