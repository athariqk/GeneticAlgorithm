#pragma once

#include "config.h"

#include "Entities/Components.h"

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class MicrobeComponent;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool running() { return m_running; }

	static Game* Get();

	static SDL_Renderer* _SDLRenderer;

	static EntityManager* GetEntityManager();

private:
	bool m_running = false;

	static EntityManager* emInstance;

	SDL_Window* _SDLWindow;

	static Game* staticInstance;
};
