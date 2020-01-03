#include "gameGUI.h"
#include "game.h"

#include "Simulation/species.h"

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

    {
        ImGui::Begin("Environment");

		ImGui::Text("Number of species: %i", Game::GetEntityManager()->
			GetGroup(Game::groupLabels::SpeciesGroup).size());

        ImGui::End();
    }

    imgui->End();
}

void GameGUI::OnImGuiClear() {
    imgui->Clear();
}
