#pragma once

#include "Components.h"
#include "Vector2D.h"

struct TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	float scale = 1;

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

	//! \brief  Construct with all transform elements parameter
	TransformComponent(float x, float y, int w, int h, float sc) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

};