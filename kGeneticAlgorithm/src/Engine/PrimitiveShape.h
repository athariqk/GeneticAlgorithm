#pragma once

#include "game.h"

#include <SDL.h>

class PrimitiveShape {
public:
	/* \todo Add enum for color codes */
	void DrawCircle(float posX, float posY, float radius,
		bool filled = false, bool edge = false)
	{
		if (filled) {
			GPU_CircleFilled(Game::screen, posX, posY, radius,
				SDL_Color{ 255, 255, 255, 150 });

			if(edge)
				GPU_Circle(Game::screen, posX, posY, radius + 1,
					SDL_Color{ 153, 153, 0, 255 });
		}
		else {
			GPU_Circle(Game::screen, posX, posY, radius,
				SDL_Color{ 255, 255, 255, 255 });
		}
	}

	void DrawRectangle(float posX, float posY, float size) {
		GPU_Rectangle(Game::screen, posX * size, posY * size,
			-posX * size, -posY * size, SDL_Color{ 255, 255, 255 });
	}
};
