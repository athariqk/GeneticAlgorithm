#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gpu.h>

class TextureManager {
public:
    static GPU_Image* LoadTexture(const char* texture);

    static void Draw(GPU_Image* tex, GPU_Rect* src, GPU_Rect* dest);
};
