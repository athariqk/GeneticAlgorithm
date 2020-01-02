#pragma once

#include "game.h"

#include <SDL.h>

class PrimitiveShape {
public:
	static void DrawCircle(float posX, float posY, float radius)
	{
        GPU_Circle(Game::screen, posX, posY, radius, SDL_Color{255, 255, 255, 255});
	}
};
