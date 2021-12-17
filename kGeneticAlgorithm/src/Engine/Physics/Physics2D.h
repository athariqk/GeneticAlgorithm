#pragma once

#include "box2d/box2d.h"

#include <memory>

class Physics2D {
public:
	Physics2D() {};
	~Physics2D() = default;

	void Init();

	void Step();

	float GetTimeStep() { return timeStep; }
	void SetTimeStep(float value) { timeStep = value; }

	float GetVelocityIterations() { return velocityIterations; }
	void SetVelocityIterations(float value) { velocityIterations = value; }

	float GetPositionIterations() { return positionIterations; }
	void SetPositionIterations(float value) { positionIterations = value; }

	b2Body* CreateBody(const b2BodyDef* bodyDef);

private:
	std::unique_ptr<b2World> world;

private:
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};
