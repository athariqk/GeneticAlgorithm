#include "TransformComponent.h"

#include "Camera.h"
#include "scene.h"

Vector2D TransformComponent::GetScreenPosition() const { return Scene::Get()->GetCamera().WorldToScreen(position); }
