#pragma once

class PMComponent
{
public:
	virtual ~PMComponent() {};

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void OnCollision() = 0;
};