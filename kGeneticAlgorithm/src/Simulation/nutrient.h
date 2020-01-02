#pragma once
#include "config.h"

#include "Entities/Components.h"
#include "PrimitiveShape.h"

#include <random>

class Nutrient : public Component {
public:
	Nutrient(int energy) : energy(energy) {}
	~Nutrient() {}

	int energy;

	void OnInit() override {
		transform = &entity->AddComponent<TransformComponent>
			(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10,
				32, 32, 0.1f);
		sprite = &entity->AddComponent<SpriteComponent>("assets/cell.png");

        collider = &entity->AddComponent<ColliderComponent>("nutrient");
	}

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
    ColliderComponent* collider;
};
