#include "Physics2D.h"

#include "Logger.h"

void Physics2D::Init()
{
	// Create physics world with no gravity
    worldDef = b2DefaultWorldDef();
    worldDef.gravity.y = 0;
	worldId = b2CreateWorld(&worldDef);
}

void Physics2D::Step()
{
	if (!b2World_IsValid(worldId)) {
		LOG_ERROR("Trying to step simulation without physics world!");
		return;
	}

    b2World_Step(worldId, GetTimeStep(), GetSubStepCount());
}

b2BodyId Physics2D::CreateBody(const b2BodyDef* bodyDef)
{
	if (!b2World_IsValid(worldId))
		return {0};

    return b2CreateBody(worldId, bodyDef);
}
