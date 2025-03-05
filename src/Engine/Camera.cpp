//
// Created by athariqk on 04/03/2025.
//
#include "Camera.h"

#include "scene.h"

Camera::Camera() { position.Zero(); }

Camera::Camera(float x, float y) {
    position.x = x;
    position.y = y;
}

// Convert world position to screen position
Vector2D Camera::WorldToScreen(const Vector2D &worldPos) const {
    // Calculate relative position to camera
    Vector2D screenPos;
    screenPos.x = (worldPos.x - position.x) * zoom;
    screenPos.y = (worldPos.y - position.y) * zoom;

    // Add half of screen dimensions to center camera
    const auto windowRes = Scene::Get()->GetWindow().GetResolution();
    screenPos.x += windowRes.x / 2;
    screenPos.y += windowRes.y / 2;

    return screenPos;
}
