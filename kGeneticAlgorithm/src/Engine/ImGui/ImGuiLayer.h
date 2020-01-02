#pragma once

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Platform/OpenGL/ImGuiSDL.h"

#include <SDL.h>
#include <imgui.h>

class ImGuiLayer {
public:
    ImGuiLayer(SDL_Window* window, SDL_GLContext* context);
    ~ImGuiLayer();

    void OnEvent(SDL_Event& event);
    void Begin(SDL_Window* window);
	void End();
    void Clear();
};