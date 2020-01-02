#pragma once

#include "game.h"

#include <SDL.h>

class PrimitiveShape {
public:
	//! \brief From answer by Scotty Stephens
	//! \https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
	//! \with minor changes
	static void DrawCircle(float posX, float posY, float radius)
	{
        GPU_Circle(Game::screen, posX, posY, radius, SDL_Color{255, 255, 255, 255});
	}
};
