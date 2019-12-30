#include "game.h"

#include "Simulation/environment.h"
#include "Simulation/species.h"

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

EntityManager* Game::emInstance = nullptr;
Game* Game::staticInstance = nullptr;

SDL_Renderer* Game::_SDLRenderer = nullptr;
SDL_Event Game::m_event;

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

	// set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);

    std::string glsl_version = "";
#ifdef __APPLE__
    // GL 3.2 Core + GLSL 150
    glsl_version = "#version 150";
    SDL_GL_SetAttribute( // required on Mac OS
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#elif __linux__
    // GL 3.2 Core + GLSL 150
    glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#elif _WIN32
    // GL 3.0 + GLSL 130
    glsl_version = "#version 450";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
#endif

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        LOG_INFO("[Game] SDL Subsystems initialized");

        _SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL);

        _SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, 0);

        if (_SDLWindow) {
            LOG_INFO("[Game] SDL Window created, resolution: {} x {}", width, height);
        }
        if (_SDLRenderer) {
            LOG_INFO("[Game] SDL Renderer created");
            SDL_SetRenderDrawColor(_SDLRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        }
    } else {
        m_running = false;
        LOG_ERROR("[Game] Failed to initialize SDL");
        return;
    }

	SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_Window* window = _SDLWindow;
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

	// Enable vsync
    SDL_GL_SetSwapInterval(1); 

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        LOG_ERROR("Failed to initialize Glad!");
    } else {
        LOG_INFO("Glad initialized");
    }

    m_running = true;

    // Create the key input controller
    auto& controller(GetEntityManager()->AddEntity());
    controller.AddComponent<KeyEvent>();

    // Spawn nutrients around the environment
    env.spawnNutrients(20);

    // Initialize the first species
    auto& primum(GetEntityManager()->AddEntity());
    primum.AddComponent<Species>("Primum", "Primus", "Specius");

    // Spawns 10 organisms
    for (int i = 0; i < 10; i++) {
        primum.AddComponent<OrganismComponent>();
    }
    //env.addSpeciesToEnvironment(&primum, 10, true)
}

void Game::HandleEvents()
{
    SDL_PollEvent(&m_event);

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
    GetEntityManager()->Refresh();
    GetEntityManager()->Update();
}

void Game::Render()
{
    SDL_RenderClear(_SDLRenderer);
    GetEntityManager()->Draw();
    SDL_SetRenderDrawColor(_SDLRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(_SDLRenderer);
}

void Game::Clean()
{
    SDL_DestroyWindow(_SDLWindow);
    SDL_DestroyRenderer(_SDLRenderer);
    SDL_Quit();
}
