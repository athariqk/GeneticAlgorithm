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
		// ----- Environment Window|begin| ------- //
		ImGui::Begin("Environment", NULL, ImGuiWindowFlags_AlwaysAutoResize);

		auto species = Game::Get()->getEnvironment().getAllSpecies();

		if (ImGui::TreeNode("SpeciesList", "Species present: %i", species.size())) {
			for (int s = 0; s < species.size(); s++) {
				ImGui::PushID(s);

				if (ImGui::TreeNode("specificSpecies", "%s %i",
					species.at(s)->getFormattedName(false).c_str(),
					species.at(s)->getPopulationCount()))
				{
					//! \brief The organisms vector in the species class
					//! is not synchronized with the one that the entity
					//! system holds because obviously its seperated, and
					//! some pointers references mumble jumbles probably :(
					if (ImGui::TreeNode("organismsList", "Organisms")) {
						for (auto& it : species.at(s)->getOrganisms()) {
							ImGui::Text("Organism %i: %s, energy: %.0f, fitness: %.0f",
								it->getID(),
								it->getAI()->getCurrentBehaviour().c_str(),
								it->curEnergy,
								it->fitness
							);
						}

						if (!species.at(s)->getOrganisms().empty()) {
							if (ImGui::Button("Purge", ImVec2(100, 20))) {
								for (auto& it : species.at(s)->getOrganisms()) {
									it->entity->Destroy();
									species.at(s)->getOrganisms().clear();
								}
							}
						}

						ImGui::TreePop();
					}
					if (ImGui::Button("Add Organism", ImVec2(100, 25))){
						species.at(s)->addOrganism();
					}
					ImGui::TreePop();
				}
				ImGui::PopID();
			}
			ImGui::TreePop();
		}

		auto& nutrients(Game::Get()->getEntityManager().GetGroup(
			Game::groupLabels::NutrientsGroup));
		if (ImGui::TreeNode("NutrientList", "Nutrients present: %i", nutrients.size())) {
			for (int n = 0; n < nutrients.size(); n++) {
				ImGui::Text("Nutrient instance %.0f", nutrients[n]->
					GetComponent<Nutrient>().curEnergy);
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

		if (ImGui::Button("Add nutrient", ImVec2(120, 25))) {
			Game::Get()->getEnvironment().spawnNutrients(10);
		}

		ImGui::End();
		// ----- Environment Window|end| ------- //
	}
	
	{
		// ----- Simulation Window|begin| ------ //
		ImGui::Begin("Simulation", NULL, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Button("Reset", ImVec2(100, 20));

		ImGui::End();
		// ----- Simulation Window|end| -------- //
	}
	
	{
		// ----- Debug Window|begin| --------- //
		ImGui::Begin("Debug");

		auto& entities = Game::Get()->getEntityManager().GetEntities();

		ImGui::BeginGroup();
		ImGui::Text("All entities present: %i", entities.size());
		for (int i = 0; i < entities.size(); i++) {
			ImGui::PushID(i);

			ImGui::Text("Entity instance");

			ImGui::PopID();
		}
		ImGui::EndGroup();

		ImGui::End();
		// ----- Debug Window|end| --------- //
	}

    imgui->End();
}

void GameGUI::OnImGuiClear() {
    imgui->Clear();
}
