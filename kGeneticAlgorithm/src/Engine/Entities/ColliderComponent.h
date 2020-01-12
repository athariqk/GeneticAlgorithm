#pragma once
#include "EntitySystem.h"
#include "Components.h"
#include "PrimitiveShape.h"
#include "Collision.h"

#include "SDL_gpu.h"

#include <string>

class ColliderComponent : public Component {
public:
	GPU_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string t) {
		tag = t;
	}

	void OnInit() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();
	}

	void OnUpdate() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

	void OnDraw() override {
		if (debug) {
			colShape.DrawCircle(collider.x, collider.y, collider.w, { 255, 255, 255, 255 });
		}
	}

	//! \note Enable the collider shape to be visible
	bool debug = false;

private:
	PrimitiveShape colShape;
};
