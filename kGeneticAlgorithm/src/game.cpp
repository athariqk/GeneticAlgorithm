#include "game.h"

#include "Simulation/environment.h"
#include "Simulation/species.h"

#include "Vector2D.h"

Environment env;
EntityManager* entityManager = new EntityManager();

Game::Game()
{
	staticInstance = this;
	emInstance = entityManager;
}

Game::~Game()
{
	staticInstance = nullptr;
}

EntityManager* Game::emInstance = nullptr;
Game* Game::staticInstance = nullptr;

SDL_Renderer* Game::_SDLRenderer = nullptr;

Game* Game::Get() {
	return staticInstance;
}

EntityManager* Game::GetEntityManager()
{
	return emInstance;
}

void Game::Init(const char* title, int width, int height, bool fullscreen) {
	

	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		LOG_TRACE("[Game] SDL Subsystems initialized");

		_SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, flags);

		_SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, 0);

		if (_SDLWindow) {
			LOG_TRACE("[Game] SDL Window created, resolution: {} x {}", width, height);
		}
		if (_SDLRenderer) {
		LOG_TRACE("[Game] SDL Renderer created");
			SDL_SetRenderDrawColor(_SDLRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		}

		m_running = true;

		Species primum = env.createSpecies("Primum", "Primus", "Specius", 10.0f, 5.0f, 10.0f, 10.0f);
		env.addSpeciesToEnvironment(&primum, 50, true);
		env.spawnFood(20);

	} else {
		m_running = false;
		LOG_ERROR("[Game] Failed to initialize SDL");
	}
}

void Game::HandleEvents() {
	SDL_Event m_event;
	SDL_PollEvent(&m_event);

	switch (m_event.type) {
		case SDL_QUIT:
			m_running = false;
			break;
		default:
			break;
	}
}

void Game::Update() {
	GetEntityManager()->Refresh();
	GetEntityManager()->Update();
}

void Game::Render() {
	SDL_RenderClear(_SDLRenderer);
	GetEntityManager()->Draw();
	SDL_SetRenderDrawColor(_SDLRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(_SDLRenderer);
}

void Game::Clean() {
	SDL_DestroyWindow(_SDLWindow);
	SDL_DestroyRenderer(_SDLRenderer);
	SDL_Quit();
}
