#pragma once

#include "config.h"

#include "Entities/EntitySystem.h"

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include <glad/glad.h>
#include <imgui.h>

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Platform/OpenGL/ImGuiSDL.h"

class OrganismComponent;

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

    static SDL_Renderer* _SDLRenderer;

    static SDL_Event m_event;

    static EntityManager* GetEntityManager();

    enum groupLabels : std::size_t {
        Nutrients,
        Other
    };

private:
    bool m_running = false;

	bool show_demo_window = true;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    static EntityManager* emInstance;

    SDL_Window* _SDLWindow;

	SDL_GLContext gl_context;

    static Game* staticInstance;
};
