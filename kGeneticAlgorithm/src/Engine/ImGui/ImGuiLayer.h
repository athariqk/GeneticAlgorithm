#pragma once
#include "Entities/Components.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Platform/OpenGL/ImGuiSDL.h"

#include <imgui.h>

class ImGuiLayer : public Component {
public:
    //! \todo Maybe add OpenGL version option
    ImGuiLayer(SDL_Window* window, SDL_GLContext* context);
    ~ImGuiLayer();

    void OnEvent(SDL_Event event);
    void Begin(SDL_Window* window);
	void End();
    void OnClear() override;
};