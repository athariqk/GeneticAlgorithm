#pragma once

struct SDL_Texture;
struct SDL_FRect;

class TextureManager {
public:
    static SDL_Texture *LoadTexture(const char *path);

    static void Draw(SDL_Texture *tex, SDL_FRect *src, SDL_FRect *dest);
};
