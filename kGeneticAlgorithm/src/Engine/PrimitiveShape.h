#pragma once

#include "game.h"

#include <SDL.h>

class PrimitiveShape {
public:
	/* \todo Add enum for color codes */
	void DrawCircle(float posX, float posY, float radius, SDL_Color
		membraneColour, bool filled = false, bool edge = false)
	{
		if (filled) {
			if (edge)
				GPU_CircleFilled(Game::screen, posX, posY, radius + 2,
					membraneColour);

			GPU_CircleFilled(Game::screen, posX, posY, radius,
				SDL_Color{ 255, 255, 255, 150 });
		}
		else {
			GPU_Circle(Game::screen, posX, posY, radius,
				SDL_Color{ 255, 255, 255, 255 });
		}
	}

	void DrawRectangle(float posX, float posY, float size) {
		GPU_Rectangle(Game::screen, 10, 10,
			40, 60, SDL_Color{ 255, 255, 255 });
	}
};
