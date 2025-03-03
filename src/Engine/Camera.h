#pragma once

#include "config.h"
#include "Vector2D.h"

class Camera {
public:
	Vector2D position;
	float zoom = 1.0f;

	Camera() {
		position.Zero();
	}

	Camera(float x, float y) {
		position.x = x;
		position.y = y;
	}

	// Convert world position to screen position
	Vector2D WorldToScreen(const Vector2D& worldPos) const {
		// Calculate relative position to camera
		Vector2D screenPos;
		screenPos.x = (worldPos.x - position.x) * zoom;
		screenPos.y = (worldPos.y - position.y) * zoom;

		// Add half of screen dimensions to center camera
		screenPos.x += WINDOW_WIDTH / 2;
		screenPos.y += WINDOW_HEIGHT / 2;

		return screenPos;
	}
};
