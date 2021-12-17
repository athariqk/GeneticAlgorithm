#include "game.h"

#include "TextureManager.h"
#include "Logger.h"

GPU_Image* TextureManager::LoadTexture(const char* texture) {
    GPU_Image* image = GPU_LoadImage(texture);

	if (image == nullptr) {
		LOG_ERROR("Could not load texture file {}!", texture);
		return nullptr;
	}

	return image;
}

void TextureManager::Draw(GPU_Image* tex, GPU_Rect* src, GPU_Rect* dest)
{
    GPU_BlitRect(tex, src, Game::Get()->getWindow().GetTarget(), dest);
}
