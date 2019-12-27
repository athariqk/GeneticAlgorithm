#pragma once
#include "config.h"

#include "Entities/Components.h"
#include "PrimitiveShape.h"

#include <random>

class Food : public Component {
public:
	Food() {}
	~Food() {}

	void OnInit() override {
		transform = &entity->AddComponent<TransformComponent>
			(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10);
		sprite = &entity->AddComponent<SpriteComponent>("assets/cell.png");
	}

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
};
