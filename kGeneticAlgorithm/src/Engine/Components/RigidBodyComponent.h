#pragma once

#include "Components.h"

#include "Physics/Physics2D.h"

class RigidBodyComponent : public Component
{
public:
	void OnInit() override;
	void OnUpdate(float delta) override;
	void OnDraw() override;
	void OnClear() override;

	void ApplyLinearImpulse(const Vector2D& impulse);
	void ApplyLinearForce(const Vector2D& force);

private:
	TransformComponent* transform;

	b2Shape* shape = nullptr;
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
};

