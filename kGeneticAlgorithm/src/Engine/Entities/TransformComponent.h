#pragma once

#include "Components.h"
#include "Vector2D.h"

#include "game.h"

struct TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	float scale = 1;

	int speed = 3;

	TransformComponent() {
		position.Zero();
	}

	//! \brief Construct with only scale parameter
	TransformComponent(float sc) {
		position.Zero();
		scale = sc;
	}

	//! \brief  Construct with x, y position paremeter
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	//! \brief Construct with x, y, and scale parameter
	TransformComponent(float x, float y, float sc)
    {
        position.x = x;
        position.y = y;
        scale = sc;
    }

	//! \brief  Construct with all transform elements parameter
	TransformComponent(float x, float y, int w, int h, float sc) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	void OnInit() override
    {
        velocity.Zero();
    }

	void OnUpdate() override
    {
        position.x += static_cast<int>(velocity.x * speed) - Game::camera.x;
		position.y += static_cast<int>(velocity.y * speed) - Game::camera.y;
    }

};
