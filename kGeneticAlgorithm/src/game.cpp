#include "game.h"

#include "Simulation/environment.h"
#include "Simulation/species.h"

#include "gameGUI.h"

#include "Vector2D.h"
#include "Entities/Components.h"

// ------------ Declare tons of stuff ------------ //
Environment		env;
EntityManager*	entityManager			= new EntityManager();
GameGUI*		gui						= new GameGUI();
// ----------------------------------------------- //
EntityManager*	Game::emInstance		= nullptr;
Game*			Game::staticInstance	= nullptr;
SDL_Renderer*	Game::_SDLRenderer		= nullptr;
SDL_Window*		Game::_SDLWindow		= nullptr;
SDL_GLContext	Game::gl_context		= nullptr;
GPU_Target*		Game::screen			= nullptr;
SDL_Event		Game::m_event;
// ----------------------------------------------- //

Game::Game()
{
    staticInstance = this;
    emInstance = entityManager;
}

Game::~Game()
{
    staticInstance = nullptr;
}

Game* Game::Get()
{
    return staticInstance;
}

EntityManager* Game::GetEntityManager()
{
    return emInstance;
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
        if (_SDLRenderer) {
            LOG_INFO("SDL Renderer created");
        }
    } else {
        m_running = false;
        LOG_ERROR("Failed to initialize SDL");
        return;
    }

    gl_context = screen->context->context;

    // Enable vsync
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

    m_running = true;

	gui->OnInit();

    // Create the key input controller
    auto& controller(GetEntityManager()->AddEntity());
    controller.AddComponent<KeyEvent>();

    // Spawn nutrients around the environment
    env.spawnNutrients(30);

    // Initialize the first species
    auto& primum(GetEntityManager()->AddEntity());
    primum.AddComponent<Species>("Primum", "Primus", "Specius");

    // Spawn 10 organisms
    for (int i = 0; i < 20; i++) {
        primum.AddComponent<OrganismComponent>();
    }
    //env.addSpeciesToEnvironment(&primum, 10, true)
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

void Game::Clean()
{
    gui->OnImGuiClear();
    GetEntityManager()->Clear();

    GPU_Quit();
    SDL_Quit();
}
