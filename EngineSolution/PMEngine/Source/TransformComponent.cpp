#include "TransformComponent.h"
#include "GameObject.h"

TransformComponent::TransformComponent() :
	LocalPosition(0.0f, 0.0f, 0.0f),
	LocalRotation(0.0f, 0.0f, 0.0f),
	LocalScale(1.0f, 1.0f, 1.0f),
	WorldPosition(0.0f, 0.0f, 0.0f),
	WorldRotation(0.0f, 0.0f, 0.0f),
	WorldScale(1.0f, 1.0f, 1.0f)
{
	CompType = "Transform";
	Awake();
}

void TransformComponent::Awake()
{
	//cout << "TransformComponent 컴포넌트 Awake호출!" << endl;
}

void TransformComponent::Start()
{
	//cout << "TransformComponent 컴포넌트 Start호출!" << endl;
}

void TransformComponent::FixedUpdate()
{
	//cout << "TransformComponent 컴포넌트 FixedUpdate 호출!" << endl;
}

void TransformComponent::Update()
{
	//cout << "TransformComponent 컴포넌트 Update 호출!" << endl;

	if (ParentGO->GetParent())
	{
		CheckParentTransform();
	}
}

void TransformComponent::LateUpdate()
{
	//cout << "TransformComponent 컴포넌트 LateUpdate 호출!" << endl;
}

void TransformComponent::Render()
{
	//cout << "TransformComponent 컴포넌트 Render 호출!" << endl;
}

void TransformComponent::CheckParentTransform()
{
	glm::vec3 pCurPos = ParentGO->GetParent()->GetTransform()->GetWorldPos();
	glm::vec3 pCurRot = ParentGO->GetParent()->GetTransform()->GetWorldRot();
	glm::vec3 pCurScale = ParentGO->GetParent()->GetTransform()->GetWorldScale ();

	if (ParentOldPosition != pCurPos)
	{
		glm::vec3 distance = pCurPos - ParentOldPosition;
		WorldPosition += distance;
		ParentOldPosition = pCurPos;
	}

	if (ParentOldRotation != pCurRot)
	{
		glm::vec3 rotate = pCurRot - ParentOldRotation;
		WorldRotation += rotate;
		ParentOldRotation = pCurRot;
	}

	if (ParentOldScale != pCurScale)
	{
		glm::vec3 size = pCurScale - ParentOldScale;
		WorldScale += size;
		ParentOldScale = pCurScale;
	}
}

void TransformComponent::SetChildTransform(TransformComponent* parentTransform)
{
	ParentOldPosition = parentTransform->GetWorldPos();
	ParentOldRotation = parentTransform->GetWorldRot();
	ParentOldScale = parentTransform->GetWorldScale();

	LocalPosition = WorldPosition - parentTransform->GetWorldPos();
	LocalRotation = WorldRotation - parentTransform->GetWorldRot();
	LocalScale = WorldScale - parentTransform->GetWorldScale();
}

void TransformComponent::SetLocalPos(glm::vec3 pos)
{
	if (ParentGO->GetParent())
	{
		glm::vec3 tempPos = ParentGO->GetParent()->GetTransform()->GetWorldPos();

		LocalPosition = pos;
		WorldPosition = tempPos + pos;
	}
	else if (!ParentGO->GetParent())
	{
		SetWorldPos(pos);
	}
}

void TransformComponent::SetLocalRot(glm::vec3 rot)
{
	if (ParentGO->GetParent())
	{
		glm::vec3 tempRot = ParentGO->GetParent()->GetTransform()->GetWorldRot();

		LocalRotation = rot;
		WorldRotation = tempRot + rot;
	}
	else if (!ParentGO->GetParent())
	{
		SetWorldRot(rot);
	}
}

void TransformComponent::SetLocalScale(glm::vec3 scale)
{
	if (ParentGO->GetParent())
	{
		glm::vec3 tempScale = ParentGO->GetParent()->GetTransform()->GetWorldScale();

		LocalScale = scale;
		WorldScale = tempScale + scale;
	}
	else if (!ParentGO->GetParent())
	{
		SetWorldScale(scale);
	}
}

void TransformComponent::SetWorldPos(glm::vec3 pos)
{
	WorldPosition = pos;

	if (ParentGO->GetParent())
	{
		glm::vec3 tempPos = ParentGO->GetParent()->GetTransform()->GetWorldPos();

		LocalPosition = WorldPosition - tempPos;
	}
}

void TransformComponent::SetWorldRot(glm::vec3 rot)
{
	WorldRotation = rot;

	if (ParentGO->GetParent())
	{
		glm::vec3 tempRot = ParentGO->GetParent()->GetTransform()->GetWorldRot();

		LocalRotation = WorldPosition - tempRot;
	}
}

void TransformComponent::SetWorldScale(glm::vec3 scale)
{
	WorldScale = scale;

	if (ParentGO->GetParent())
	{
		glm::vec3 tempScale = ParentGO->GetParent()->GetTransform()->GetWorldScale();

		LocalScale = WorldScale - tempScale;
	}
}