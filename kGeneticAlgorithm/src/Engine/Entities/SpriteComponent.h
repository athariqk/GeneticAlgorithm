#pragma once

#include "TextureManager.h"
#include "Components.h"
#include "Logger.h"

#include "SDL.h"

class SpriteComponent : public Component {
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void OnInit() override {
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void OnUpdate() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void OnDraw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
};