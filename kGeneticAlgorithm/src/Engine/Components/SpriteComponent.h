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
	}

	void OnInit() override {
		transform = &entity->GetComponent<TransformComponent>();

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void OnUpdate(float delta) override {
		destRect.x = transform->position.x - (destRect.w / 2);
		destRect.y = transform->position.y - (destRect.h / 2);
	}

	void OnDraw() override {
        TextureManager::Draw(texture, NULL, &destRect);
	}

private:
	TransformComponent* transform;
	GPU_Image* texture;
	GPU_Rect destRect;
};
