#include "ImGui/ImGuiLayer.h"

#include <SDL3/SDL_render.h>

#include "Backends/ImGuiSDL.h"
#include "Backends/ImGuiSDLRenderer.h"
#include "Logger.h"

ImGuiLayer::ImGuiLayer(SDL_Window *window) {
    if (!window) {
        LOG_ERROR("Failed to initialize ImGui, window is missing!");
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui_ImplSDL3_InitForSDLRenderer(window, SDL_GetRenderer(window));
    ImGui_ImplSDLRenderer3_Init(SDL_GetRenderer(window));

    ImGui::StyleColorsClassic();

    LOG_INFO("ImGui Initialized");
}

void ImGuiLayer::OnEvent(const SDL_Event &event) { ImGui_ImplSDL3_ProcessEvent(&event); }

void ImGuiLayer::Begin() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End(SDL_Window *window) {
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), SDL_GetRenderer(window));
}

void ImGuiLayer::Clear() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
