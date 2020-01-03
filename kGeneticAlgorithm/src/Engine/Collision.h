#pragma once

#include <SDL_gpu.h>

class ColliderComponent;

class Collision {
public:
	static bool AABB(const GPU_Rect& rectA, const GPU_Rect& rectB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};
