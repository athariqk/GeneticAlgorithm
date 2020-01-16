#include "game.h"

#include "Simulation/environment.h"
#include "Simulation/species.h"
#include "Simulation/organism.h"

#include "gameGUI.h"

#include "Vector2D.h"
#include "Components/Components.h"

EntityManager	entityManager;
GameGUI			gui;
Environment		env;
Game*			Game::staticInstance	= nullptr;
SDL_Event		Game::m_event;
// There is a method in SDL-GPU for a camera
// (GPU_Camera), maybe this could be used instead?
GPU_Rect		Game::camera			= { 0,0, WINDOW_WIDTH, WINDOW_HEIGHT };

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
	mainWindow = new Window(title, width, height, fullscreen);

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

	LOG_TRACE("----- End of system informations -----");

	// Start the game loop
	m_running = true;

	// Initialize ImGui
	gui.OnInit();

	auto& controller(entityManager.AddEntity());
	controller.AddComponent<KeyEvent>();

	env.spawnNutrients(30);

	/* Initial species */
	env.addSpeciesToEnvironment("Primum", "Primus", "specius");
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
	case SDL_WINDOWEVENT:
		switch (m_event.window.event) {
		case SDL_WINDOWEVENT_RESIZED:
			GPU_SetWindowResolution(m_event.window.data1,
				m_event.window.data2);
			LOG_INFO("Window resolution changed: {} x {}",
				m_event.window.data1, m_event.window.data2);
			break;
		default:
			break;
		}
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
	/* Solid background color */
	GPU_ClearRGBA(mainWindow->GetTarget(), 70, 130, 180, 255);

	entityManager.Draw();

	GPU_FlushBlitBuffer();

	gui.OnImGuiRender();

	SDL_GL_MakeCurrent(mainWindow->GetWindow(),
		mainWindow->GetGLContext());

	GPU_Flip(mainWindow->GetTarget());
}

Window& Game::getWindow() {
	return *mainWindow;
}

EntityManager& Game::getEntityManager()
{
	return entityManager;
}

Environment& Game::getEnvironment() {
	return env;
}

GameGUI& Game::getGUI() {
	return gui;
}

void Game::Clean()
{
	gui.OnImGuiClear();
	entityManager.Clear();
	delete(mainWindow);

	GPU_Quit();
	SDL_Quit();
}
