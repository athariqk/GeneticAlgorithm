#pragma once

#include "game.h"

#include <SDL.h>

class PrimitiveShape {
public:
	void DrawCircle(float posX, float posY, float radius)
	{
		GPU_Circle(Game::screen, posX, posY, radius, SDL_Color{ 255, 255, 255, 255 });
	}

	void DrawRectangle(float posX, float posY, float size) {
		GPU_Rectangle(Game::screen, posX * size, posY * size,
			-posX * size, -posY * size, SDL_Color{ 255, 255, 255 });
	}
};
