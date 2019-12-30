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

    const char* glsl_version = "";
#ifdef _WIN32
    // GL 3.0 + GLSL 130
    glsl_version = "#version 110";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        LOG_INFO("[Game] SDL Subsystems initialized");

        _SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL);

        _SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, SDL_RENDERER_ACCELERATED);

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
    gl_context = SDL_GL_CreateContext(window);

	// Enable vsync
    SDL_GL_SetSwapInterval(1); 

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        LOG_ERROR("Failed to initialize Glad!");
    } else {
        LOG_INFO("Glad initialized");
    }

	// Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsClassic();

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
    ImGui_ImplSDL2_ProcessEvent(&m_event);

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
    SDL_SetRenderDrawColor(_SDLRenderer, clear_color.x * 255, clear_color.y * 255, clear_color.z * 255, clear_color.w * 255);
    SDL_RenderClear(_SDLRenderer);
    SDL_SetRenderDrawColor(_SDLRenderer, 0xEE, 0xEE, 0xEE, 0xFF);

	GetEntityManager()->Draw();

	// Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(_SDLWindow);
    ImGui::NewFrame();

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // Rendering
    ImGui::Render();
    //SDL_GL_MakeCurrent(window, gl_context); !!!This line must be commented
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    //glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w); !!!This line must be commented
    //glClear(GL_COLOR_BUFFER_BIT); !!!This line must be commented
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(_SDLWindow);
    SDL_RenderPresent(_SDLRenderer);
}

void Game::Clean()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(_SDLWindow);
    SDL_Quit();
}
