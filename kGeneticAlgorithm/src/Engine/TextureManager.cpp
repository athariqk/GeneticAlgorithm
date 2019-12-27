#include "game.h"

#include "TextureManager.h"
#include "Logger.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	if (Game::_SDLRenderer == nullptr) {
		LOG_ERROR("[TextureManager] Renderer is not initialized!");
		return nullptr;
	}

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::_SDLRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (tex == nullptr) {
		LOG_ERROR("[TextureManager] Could not load texture file {}!", texture);
		return NULL;
	}
	LOG_TRACE("[TextureManager] Loaded texture file {}", texture);

	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::_SDLRenderer, tex, &src, &dest);
}
