#include "SpriteComponent.h"

#include <SDL3/SDL_render.h>

#include "TextureManager.h"
#include "TransformComponent.h"
#include "Vector2D.h"

SpriteComponent::SpriteComponent(const char* path)
{
	texture = TextureManager::LoadTexture(path);
}

SpriteComponent::~SpriteComponent()
{
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void SpriteComponent::OnInit() {
	transform = &entity->GetComponent<TransformComponent>();

	destRect.w = transform->width * transform->scale;
	destRect.h = transform->height * transform->scale;
}

void SpriteComponent::OnUpdate(float delta) {
	const Vector2D screenPos = transform->GetScreenPosition();

	destRect.x = screenPos.x - (destRect.w / 2);
	destRect.y = screenPos.y - (destRect.h / 2);
}

void SpriteComponent::OnDraw() {
	TextureManager::Draw(texture, nullptr, &destRect);
}
