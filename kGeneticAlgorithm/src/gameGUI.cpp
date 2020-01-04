#include "gameGUI.h"
#include "game.h"

#include "Simulation/species.h"
#include "Simulation/organism.h"
#include "Simulation/environment.h"

#include "misc/cpp/imgui_stdlib.h"

void GameGUI::OnInit(){
    imgui = new ImGuiLayer(Game::Get()->_SDLWindow, Game::Get()->getGLContext());
}

void GameGUI::OnImGuiEvent()
{
    imgui->OnEvent(Game::Get()->m_event);
}

void GameGUI::OnImGuiRender()
{
    imgui->Begin(Game::Get()->_SDLWindow);

	{
		// ----- Environment window|begin| ------- //
		ImGui::Begin("Environment");

		auto species = Game::Get()->getEntityManager().GetGroup(
			Game::groupLabels::SpeciesGroup);
		ImGui::Text("Number of species present: %i", species.size());

		// ----- Create new species modal|begin| ------- //
		if (ImGui::Button("Create species", ImVec2(120, 25)))
			ImGui::OpenPopup("Create a new species");

		if(ImGui::BeginPopupModal("Create a new species", NULL,
			ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Enter the species' name");
			ImGui::InputText("Genus", &sGenus);
			ImGui::InputText("Epithet", &sEpithet);
			ImGui::Separator();
			if (ImGui::Button("Create", ImVec2(100, 20))) {
				if (sGenus.empty() || sEpithet.empty()) {
					LOG_ERROR("Genus or species is not valid!");
				}
				else {
					Game::Get()->getEnvironment().addSpeciesToEnvironment(
						sGenus, sGenus, sEpithet);
					sGenus.clear();
					sEpithet.clear();
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(100, 20))) {
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		// ----- Create new species popup|end| ------- //



		ImGui::End();
		// ----- Environment window|end| ------- //
	}

    imgui->End();
}

void GameGUI::OnImGuiClear() {
    imgui->Clear();
}
