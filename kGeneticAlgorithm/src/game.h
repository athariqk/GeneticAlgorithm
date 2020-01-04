#pragma once
#include "config.h"

#include "Entities/EntitySystem.h"

#include <SDL.h>
#include <SDL_gpu.h>

#include <glad/glad.h>

#include <string>

class Environment;

class Game {
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

	EntityManager& getEntityManager();

	Environment& getEnvironment();

	SDL_GLContext& getGLContext();

	static SDL_Renderer* _SDLRenderer;
	static SDL_Window* _SDLWindow;
	static GPU_Target* screen;
	static SDL_Event m_event;
	static GPU_Rect camera;

	enum groupLabels : std::size_t {
		NutrientsGroup,
		SpeciesGroup,
		OrganismsGroup,
		Other
	};

private:
	bool m_running = false;

	static Game* staticInstance;
};
