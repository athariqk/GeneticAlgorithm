#pragma once

#include "config.h"

#include "Entities/EntitySystem.h"

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include <glad/glad.h>

class OrganismComponent;

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

	static SDL_Event m_event;

	static EntityManager* GetEntityManager();

	enum groupLabels : std::size_t {
        Nutrients,
		Other
    };

private:
	bool m_running = false;

	static EntityManager* emInstance;

	SDL_Window* _SDLWindow;

	static Game* staticInstance;
};
