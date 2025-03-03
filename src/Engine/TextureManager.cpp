#include "scene.h"

#include "TextureManager.h"
#include "Logger.h"

#include <SDL3_image/SDL_image.h>

SDL_Texture* TextureManager::LoadTexture(const char* path) {
    SDL_Renderer* renderer = Scene::Get()->GetWindow().GetRenderer();
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
	if (texture == nullptr) {
		LOG_ERROR("Could not load texture file {}: {}", path, SDL_GetError());
		return nullptr;
	}

	return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_FRect* src, SDL_FRect* dest)
{
    SDL_Renderer* renderer = Scene::Get()->GetWindow().GetRenderer();
    SDL_RenderTexture(renderer, tex, src, dest);
}
