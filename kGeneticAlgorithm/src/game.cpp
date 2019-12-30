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

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        LOG_INFO("[Game] SDL Subsystems initialized");

        _SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL
			| SDL_WINDOW_ALLOW_HIGHDPI);

        _SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, SDL_RENDERER_SOFTWARE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

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

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    ImGui_ImplSDL2_InitForOpenGL(_SDLWindow, gl_context);
    ImGui_ImplOpenGL3_Init("#version 460");

    // Setup style
    ImGui::StyleColorsClassic();

	// Report OpenGL info
	LOG_INFO("OpenGL version: {}", glGetString(GL_VERSION));
	LOG_INFO("GLSL version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	LOG_INFO("Vendor: {}", glGetString(GL_VENDOR));
	LOG_INFO("Renderer: {}", glGetString(GL_RENDERER));

    m_running = true;

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

void Game::HandleEvents()
{
    SDL_PollEvent(&m_event);

    switch (m_event.type) {
        ImGui_ImplSDL2_ProcessEvent(&m_event);

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

	//GetEntityManager()->Draw();

	// Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(_SDLWindow);
    ImGui::NewFrame();

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(_SDLWindow);
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
