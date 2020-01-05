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

	// ----- Environment window|begin| ------- //
	{
		ImGui::Begin("Environment", NULL, ImGuiWindowFlags_AlwaysAutoResize);

		auto& species(Game::Get()->getEntityManager().GetGroup(
			Game::groupLabels::SpeciesGroup));
		if (ImGui::TreeNode("SpeciesList", "Species present: %i", species.size())) {
			for (int s = 0; s < species.size(); s++) {
				ImGui::Text(species[s]->GetComponent<Species>().
					getFormattedName(true).c_str());
			}
			ImGui::TreePop();
		}

		auto& organisms(Game::Get()->getEntityManager().GetGroup(
			Game::groupLabels::OrganismsGroup));
		if (ImGui::TreeNode("OrganismList", "Organisms present: %i", organisms.size())) {
			for (int o = 0; o < organisms.size(); o++) {
				ImGui::Text("Organism %i: %s, energy %.0f",
					organisms[o]->GetComponent<OrganismComponent>().getID(),
					organisms[o]->GetComponent<OrganismAI>().getCurrentBehaviour().c_str(),
					organisms[o]->GetComponent<OrganismComponent>().energy);
			}

			if (!Game::Get()->getEntityManager().
				GetGroup(Game::groupLabels::OrganismsGroup).empty())
			{
				if (ImGui::Button("Clear organisms", ImVec2(100, 20)))
					Game::Get()->getEnvironment().clearOrganisms();
			}

			ImGui::TreePop();
		}

		auto& nutrients(Game::Get()->getEntityManager().GetGroup(
			Game::groupLabels::NutrientsGroup));
		if (ImGui::TreeNode("NutrientList", "Nutrients present: %i", nutrients.size())) {
			for (int n = 0; n < nutrients.size(); n++) {
				ImGui::Text("Nutrient instance %.0f", nutrients[n]->
					GetComponent<Nutrient>().energy);
			}
			ImGui::TreePop();
		}

		ImGui::Separator();

		if (ImGui::Button("Add species", ImVec2(120, 25)))
			ImGui::OpenPopup("Create a new species");

		// ----- Create new species modal|begin| ------- //
		{
			if (ImGui::BeginPopupModal("Create a new species", NULL,
				ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Enter the species' name");
				ImGui::InputText("Genus", &sGenus);
				ImGui::InputText("Epithet", &sEpithet);
				ImGui::Separator();
				if (ImGui::Button("Create", ImVec2(100, 20))) {
					if (sGenus.empty() || sEpithet.empty()) {
						LOG_ERROR("Genus or epithet is not valid!");
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
					sGenus.clear();
					sEpithet.clear();
				}

				ImGui::EndPopup();
			}
		}
		// ----- Create new species popup|end| ------- //

		ImGui::SameLine();


		if (ImGui::Button("Add organism", ImVec2(150, 25)))
			Game::Get()->getEnvironment().addOrganismToEnvironment();

		ImGui::End();
	}
	// ----- Environment window|end| ------- //

	// ----- Simulation window|begin| ------ //
	{
		ImGui::Begin("Simulation", NULL, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Button("Reset", ImVec2(100, 20));

		ImGui::End();
	}
	// ----- Simulation window|end| -------- //

    imgui->End();
}

void GameGUI::OnImGuiClear() {
    imgui->Clear();
}
