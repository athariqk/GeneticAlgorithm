#include "Physics2D.h"

#include "Logger.h"

void Physics2D::Init()
{
	// Create physics world with no gravity
	world = std::make_unique<b2World>(b2Vec2());
}

void Physics2D::Step()
{
	if (!world) {
		LOG_ERROR("Trying to step simulation without physics world!");
		return;
	}

	world->Step(timeStep, velocityIterations, positionIterations);
}

b2Body* Physics2D::CreateBody(const b2BodyDef* bodyDef)
{
	if (!world)
		return nullptr;

	return world->CreateBody(bodyDef);
}
