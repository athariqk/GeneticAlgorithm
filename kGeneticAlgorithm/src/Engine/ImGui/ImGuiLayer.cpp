#include "ImGui/ImGuiLayer.h"
#include "Logger.h"

#include <glad/glad.h>

ImGuiLayer::ImGuiLayer(SDL_Window* window, SDL_GLContext* context)
{
	if (!window) {
        LOG_ERROR("Failed to initialize ImGui, window is missing!");
        return;
	}

	if (context == nullptr) {
        LOG_ERROR("Failed to initialize imGui, GL context is missing!");
        return;
	}

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Setup style
    ImGui::StyleColorsClassic();

	LOG_INFO("ImGui Initialized");
}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnEvent(SDL_Event event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void ImGuiLayer::Begin(SDL_Window* window)
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::Clear() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}