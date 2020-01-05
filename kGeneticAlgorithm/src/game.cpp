#include "game.h"

#include "Simulation/environment.h"
#include "Simulation/species.h"
#include "Simulation/organism.h"

#include "gameGUI.h"

#include "Vector2D.h"
#include "Entities/Components.h"

// ------------ Declare tons of stuff ------------ //
EntityManager	entityManager;
GameGUI			gui;
Environment		env;
SDL_GLContext	gl_context;
// ----------------------------------------------- //
Game*			Game::staticInstance	= nullptr;
SDL_Renderer*	Game::_SDLRenderer		= nullptr;
SDL_Window*		Game::_SDLWindow		= nullptr;
GPU_Target*		Game::screen			= nullptr;
//! \note There is a method in sdl-gpu for camera "GPU_Camera"
//! maybe that could be used instead?
GPU_Rect		Game::camera			= { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
SDL_Event		Game::m_event;
// ----------------------------------------------- //

Game::Game()
{
	staticInstance = this;
}

Game::~Game()
{
	staticInstance = nullptr;
}

Game* Game::Get()
{
	return staticInstance;
}

void Game::Init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		LOG_INFO("SDL Subsystems initialized");

		screen = GPU_Init(WINDOW_WIDTH, WINDOW_HEIGHT, GPU_DEFAULT_INIT_FLAGS);

		if (screen == NULL) {
			LOG_ERROR("Failed to initialize SDL_gpu!");
			return;
		}

		_SDLWindow = SDL_GetWindowFromID(screen->context->windowID);
		gl_context = screen->context->context;

		if (_SDLWindow) {
			LOG_INFO("SDL Window created, resolution: {} x {}", width, height);
		}
	}
	else {
		m_running = false;
		LOG_ERROR("Failed to initialize SDL");
		return;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		m_running = false;
		LOG_ERROR("Failed to initialize Glad!");
	}
	else {
		LOG_INFO("Glad initialized");
	}

	// Report OpenGL info
	LOG_INFO("OpenGL version: {}", glGetString(GL_VERSION));
	LOG_INFO("GLSL version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	LOG_INFO("Vendor: {}", glGetString(GL_VENDOR));
	LOG_INFO("Renderer: {}", glGetString(GL_RENDERER));

	// Start the game loop
	m_running = true;

	// Initialize ImGui
	gui.OnInit();

	auto& controller(entityManager.AddEntity());
	controller.AddComponent<KeyEvent>();

	env.spawnNutrients(30);

	// The species should be created first inside the species
	// class, but for testing purposes the organisms could
	// be spawned here instead
	for (int i = 0; i < 20; i++) {
		auto& organismInstance(entityManager.AddEntity());;
		organismInstance.AddComponent<OrganismComponent>(100);
		organismInstance.AddGroup(groupLabels::OrganismsGroup);
	}
}

void Game::HandleEvents()
{
	SDL_PollEvent(&m_event);

	entityManager.Event();
	gui.OnImGuiEvent();

	switch (m_event.type) {
	case SDL_QUIT:
		m_running = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
	entityManager.Refresh();
	entityManager.Update();
}

void Game::Render()
{
	GPU_ClearRGBA(screen, 0, 0, 0, 255);

	entityManager.Draw();

	GPU_FlushBlitBuffer();

	gui.OnImGuiRender();

	SDL_GL_MakeCurrent(_SDLWindow, gl_context);
	GPU_Flip(screen);
}

EntityManager& Game::getEntityManager()
{
	return entityManager;
}

Environment& Game::getEnvironment() {
	return env;
}

SDL_GLContext& Game::getGLContext() {
	return gl_context;
}

void Game::Clean()
{
	gui.OnImGuiClear();
	entityManager.Clear();

	GPU_Quit();
	SDL_Quit();
}
