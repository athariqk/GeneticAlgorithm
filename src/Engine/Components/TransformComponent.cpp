#include "TransformComponent.h"

#include "scene.h"
#include "Camera.h"

Vector2D TransformComponent::GetScreenPosition() const {
	return Scene::Get()->GetCamera().WorldToScreen(position);
}
