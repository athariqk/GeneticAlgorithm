#pragma once
#include "config.h"

#include "Entities/Components.h"

#include <random>

class Nutrient : public Component {
public:
	Nutrient(int energy) : curEnergy(energy) {}
	~Nutrient() {}

	float curEnergy;

	void OnInit() override {
		id = std::rand() % 20 + 5;
		transform = &entity->AddComponent<TransformComponent>
			(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10, 32, 32, 0.05f);
		sprite = &entity->AddComponent<SpriteComponent>("assets/nutrient.png");
		collider = &entity->AddComponent<ColliderComponent>("nutrient");
	}

	void OnUpdate() {
		if (curEnergy < 0)
			entity->Destroy();

		/* For that "sucking" effect */
		if(caught)
			transform->position = transform->position.Lerp(transform->position, organismPos, 0.03f);
	}

	//! \todo Implement proper ID counting
	size_t getID() const {
		return id;
	}

	bool caught = false;
	Vector2D organismPos;

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	ColliderComponent* collider;

	size_t id = 0;
};
