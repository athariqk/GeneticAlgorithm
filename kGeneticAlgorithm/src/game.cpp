#include "game.h"

#include "Simulation/environment.h"
#include "Simulation/species.h"

#include "gameGUI.h"

#include "Vector2D.h"
#include "Entities/Components.h"

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

// ------------------------------------- //
EntityManager* Game::emInstance = nullptr;
Game* Game::staticInstance = nullptr;
SDL_Renderer* Game::_SDLRenderer = nullptr;
SDL_Window* Game::_SDLWindow = nullptr;
SDL_GLContext Game::gl_context = nullptr;
SDL_Event Game::m_event;
// ------------------------------------- //

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
        LOG_INFO("[Game] SDL Subsystems initialized");

        _SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

        //_SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, SDL_RENDERER_SOFTWARE);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        if (_SDLWindow) {
            LOG_INFO("[Game] SDL Window created, resolution: {} x {}", width, height);
        }
        if (_SDLRenderer) {
            LOG_INFO("[Game] SDL Renderer created");
        }
    } else {
        m_running = false;
        LOG_ERROR("[Game] Failed to initialize SDL");
        return;
    }

    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    gl_context = SDL_GL_CreateContext(_SDLWindow);

    // Enable vsync
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        LOG_ERROR("Failed to initialize Glad!");
    } else {
        LOG_INFO("Glad initialized");
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Report OpenGL info
    LOG_INFO("OpenGL version: {}", glGetString(GL_VERSION));
    LOG_INFO("GLSL version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    LOG_INFO("Vendor: {}", glGetString(GL_VENDOR));
    LOG_INFO("Renderer: {}", glGetString(GL_RENDERER));

    m_running = true;

	// Create GUI
	auto& GUI(GetEntityManager()->AddEntity());
    GUI.AddComponent<GameGUI>();

    // Create the key input controller
    auto& controller(GetEntityManager()->AddEntity());
    controller.AddComponent<KeyEvent>();

    // Spawn nutrients around the environment
    env.spawnNutrients(20);

    // Initialize the first species
    auto& primum(GetEntityManager()->AddEntity());
    primum.AddComponent<Species>("Primum", "Primus", "Specius");

    // Spawn 10 organisms
    for (int i = 0; i < 10; i++) {
        primum.AddComponent<OrganismComponent>();
    }
    //env.addSpeciesToEnvironment(&primum, 10, true)
}

SDL_GLContext* Game::GetContext()
{
    return &gl_context;
}

void Game::HandleEvents()
{
    SDL_PollEvent(&m_event);

    switch (m_event.type) {
        GetEntityManager()->Event();

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
    glClearColor(0, 0, 0, 0);
    GetEntityManager()->Draw();
    SDL_GL_SwapWindow(_SDLWindow);
}

void Game::Clean()
{
    GetEntityManager()->Clear();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(_SDLWindow);
    SDL_Quit();
}
