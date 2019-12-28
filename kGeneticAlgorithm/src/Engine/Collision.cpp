#include "Collision.h"
#include "Entities/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	if (rectA.x + rectB.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const ColliderComponent & colA, const ColliderComponent & colB)
{
	if (AABB(colA.collider, colB.collider)) {
		LOG_INFO("Collider {} hit colider: {}", colA.tag, colB.tag);
		return true;
	}
	else {
		return false;
	}
}
