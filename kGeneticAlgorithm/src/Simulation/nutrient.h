#pragma once
#include "config.h"

#include "Entities/Components.h"

#include <random>

class Nutrient : public Component {
public:
	Nutrient(int energy) : energy(energy) {}
	~Nutrient() {}

	float energy;

	void OnInit() override {
		transform = &entity->AddComponent<TransformComponent>
			(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10,
				32, 32, 0.05f);
		sprite = &entity->AddComponent<SpriteComponent>("assets/nutrient.png");

		collider = &entity->AddComponent<ColliderComponent>("nutrient");
	}

	void OnUpdate() {
		if (energy < 0)
			entity->Destroy();
	}

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	ColliderComponent* collider;
};
