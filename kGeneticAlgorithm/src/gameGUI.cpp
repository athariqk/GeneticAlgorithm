#include "gameGUI.h"

#include "game.h"

void GameGUI::OnInit(){
    imgui = new ImGuiLayer(Game::Get()->_SDLWindow, Game::GetContext());
}

void GameGUI::OnImGuiEvent()
{
    imgui->OnEvent(Game::Get()->m_event);
}

void GameGUI::OnImGuiRender()
{
    imgui->Begin(Game::Get()->_SDLWindow);

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");

        ImGui::Text("This is some useful text.");
        ImGui::Checkbox("Demo Window", &show_demo_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

        if (ImGui::Button("Button"))
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    imgui->End();
}

void GameGUI::OnImGuiClear() {
    imgui->Clear();
}