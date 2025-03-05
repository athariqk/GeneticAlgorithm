#pragma once

#include "Vector2D.h"

class Camera {
public:
    Vector2D position;
    float zoom = 1.0f;

    Camera();

    Camera(float x, float y);

    // Convert world position to screen position
    Vector2D WorldToScreen(const Vector2D &worldPos) const;
};
