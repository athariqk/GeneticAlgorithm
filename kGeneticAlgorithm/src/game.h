#pragma once
#include "config.h"

#include "Components/EntitySystem.h"
#include "Window.h"

#include <SDL.h>
#include <SDL_gpu.h>

#include <glad/glad.h>

#include <string>

class Environment;

class GameGUI;

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

	Window& getWindow();
	EntityManager& getEntityManager();
	Environment& getEnvironment();
	GameGUI& getGUI();

	static GPU_Rect camera;
	static SDL_Event m_event;

	enum groupLabels : std::size_t {
		NutrientsGroup,
		SpeciesGroup,
		OrganismsGroup,
		Other
	};

private:
	bool m_running = false;

	static Game* staticInstance;

	Window* mainWindow;
};
