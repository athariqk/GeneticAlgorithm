#include "game.h"

#include "Simulation/environment.h"
#include "Simulation/species.h"
#include "Simulation/organism.h"

#include "gameGUI.h"

#include "Vector2D.h"
#include "Entities/Components.h"

// ------------ Declare tons of stuff ------------ //
Environment*	env						= new Environment();
EntityManager*	entityManager			= new EntityManager();
GameGUI*		gui						= new GameGUI();
// ----------------------------------------------- //
EntityManager*	Game::emInstance		= nullptr;
Game*			Game::staticInstance	= nullptr;
SDL_Renderer*	Game::_SDLRenderer		= nullptr;
SDL_Window*		Game::_SDLWindow		= nullptr;
SDL_GLContext	Game::gl_context		= nullptr;
GPU_Target*		Game::screen			= nullptr;
//! \note There is a method in sdl-gpu for camera "GPU_Camera"
//! maybe that could be used instead?
GPU_Rect		Game::camera			= { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
SDL_Event		Game::m_event;
// ----------------------------------------------- //

Game::Game()
{
    staticInstance = this;
    emInstance = entityManager;
	//envInstance = env;
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

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        LOG_INFO("SDL Subsystems initialized");

        screen = GPU_Init(WINDOW_WIDTH, WINDOW_HEIGHT, GPU_DEFAULT_INIT_FLAGS);

		if (screen == NULL) {
			LOG_ERROR("Failed to initialize SDL_gpu!");
			return;
		}

        _SDLWindow = SDL_GetWindowFromID(screen->context->windowID);

		//_SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
		//    SDL_WINDOWPOS_CENTERED, width, height, flags |
		//	SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

		//_SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, SDL_RENDERER_SOFTWARE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        if (_SDLWindow) {
            LOG_INFO("SDL Window created, resolution: {} x {}", width, height);
        }
    } else {
        m_running = false;
        LOG_ERROR("Failed to initialize SDL");
        return;
    }

    gl_context = screen->context->context;

    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        LOG_ERROR("Failed to initialize Glad!");
    } else {
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
	gui->OnInit();

    auto& controller(GetEntityManager()->AddEntity());
    controller.AddComponent<KeyEvent>();

    env->spawnNutrients(30);

	// For testing purposes, species could later be created in the gui
	env->addSpeciesToEnvironment("Primum", "Primus", "specius");
	env->addSpeciesToEnvironment("Secundum", "Secundus", "specius");
	env->addSpeciesToEnvironment("Tersium", "Tersius", "specius");

	for (int i = 0; i < 20; i++) {
		auto& organismInstance(GetEntityManager()->AddEntity());;
		organismInstance.AddComponent<OrganismComponent>();
	}
}

void Game::HandleEvents()
{
    SDL_PollEvent(&m_event);

    switch (m_event.type) {
        GetEntityManager()->Event();
        gui->OnImGuiEvent();

    case SDL_QUIT:
        m_running = false;
        break;
    default:
        break;
    }
}

void Game::Update()
{
    GetEntityManager()->Refresh();
    GetEntityManager()->Update();
}

void Game::Render()
{
    GPU_ClearRGBA(screen, 0, 0, 0, 255);

    GetEntityManager()->Draw();

    GPU_FlushBlitBuffer();

    gui->OnImGuiRender();

    SDL_GL_MakeCurrent(_SDLWindow, gl_context);
    GPU_Flip(screen);
}

EntityManager* Game::GetEntityManager()
{
	return emInstance;
}

void Game::Clean()
{
    gui->OnImGuiClear();
    GetEntityManager()->Clear();

    GPU_Quit();
    SDL_Quit();
}
