#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class TransformComponent : public Component
{
private:
	glm::vec3 LocalPosition;
	glm::vec3 LocalRotation;
	glm::vec3 LocalScale;

	glm::vec3 WorldPosition;
	glm::vec3 WorldRotation;
	glm::vec3 WorldScale;

	glm::vec3 ParentOldPosition;
	glm::vec3 ParentOldRotation;
	glm::vec3 ParentOldScale;

public:
	TransformComponent();
	~TransformComponent() {};

	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	//////////////////////////////////////

	void SetLocalPos(glm::vec3 pos);
	void SetLocalRot(glm::vec3 rot);
	void SetLocalScale(glm::vec3 scale);

	void SetWorldPos(glm::vec3 pos);
	void SetWorldRot(glm::vec3 rot);
	void SetWorldScale(glm::vec3 scale);

	void CheckParentTransform();
	void SetChildTransform(TransformComponent* parentTransform);

	glm::vec3 GetLocalPos() const
	{ 
		return LocalPosition;
	}
	glm::vec3 GetLocalRot() const
	{ 
		return LocalRotation;
	}
	glm::vec3 GetLocalScale() const
	{ 
		return LocalScale;
	}

	glm::vec3 GetWorldPos() const
	{ 
		return WorldPosition;
	}
	glm::vec3 GetWorldRot() const
	{ 
		return WorldRotation;
	}
	glm::vec3 GetWorldScale() const
	{ 
		return WorldScale;
	}
};
