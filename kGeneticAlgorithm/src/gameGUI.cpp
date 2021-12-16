#include "gameGUI.h"
#include "game.h"

#include "Simulation/species.h"
#include "Simulation/organism.h"
#include "Simulation/environment.h"

#include "misc/cpp/imgui_stdlib.h"

void GameGUI::OnInit(){
    imgui = new ImGuiLayer(Game::Get()->getWindow().GetWindow(),
		Game::Get()->getWindow().GetGLContext());
}

void GameGUI::OnImGuiEvent()
{
    imgui->OnEvent(Game::Get()->m_event);
}

void GameGUI::OnImGuiRender()
{
    imgui->Begin(Game::Get()->getWindow().GetWindow());

	{
		/* ----- Environment Window|begin| ------- */
		ImGui::Begin("Environment", NULL, ImGuiWindowFlags_AlwaysAutoResize);

		auto species = Game::Get()->getEnvironment().getAllSpecies();

		if (ImGui::TreeNode("SpeciesList", "Species present: %i", species.size())) {
			for (int s = 0; s < species.size(); s++) {
				ImGui::PushID(s);

				if (ImGui::TreeNode("specificSpecies", "%s, Pop: %i",
					species[s]->getFormattedName(false).c_str(),
					species[s]->getPopulationCount()))
				{
					if (ImGui::TreeNode("organismsList", "Organisms")) {
						for (int i = 0; i < species[s]->organisms.size(); i++) {
							ImGui::PushID(i);
							auto organism = species[s]->organisms[i];
							if (ImGui::TreeNode("individuals", "Organism %i", organism->getID())) {
								ImGui::Text("Behaviour: %s\nEnergy: %.0f/%.0f\nSpeed: %f\nSize: %f\nAggresiveness: "
									"%f\nMembraneColour.r: %i\nMembraneColour.g: %i\nMembraneColour.rb: %i\nFitness: %.0f",
									organism->ai->getCurrentBehaviour().c_str(),
									organism->curEnergy,
									organism->genome.energyCapacity,
									organism->genome.speed,
									organism->genome.size,
									organism->genome.aggresiveness,
									organism->genome.membraneColour.r,
									organism->genome.membraneColour.g,
									organism->genome.membraneColour.b,
									organism->fitness
								);
								ImGui::TreePop();
							}
							ImGui::PopID();
						}
						ImGui::TreePop();
					}

					if (ImGui::Button("Add Organism", ImVec2(100, 25))) {
						species[s]->addOrganism();
					}

					ImGui::SameLine();

					if (ImGui::Button("Make Extinct", ImVec2(100, 25))) {
						Game::Get()->getEnvironment().
							makeExtinct(species[s]);
					}

					ImGui::TreePop();
				}
				ImGui::PopID();
			}
			ImGui::TreePop();
		}

		auto& nutrients(Game::Get()->getEntityManager().GetGroup(Game::groupLabels::NutrientsGroup));
		if (ImGui::TreeNode("NutrientList", "Nutrients available: %i", nutrients.size())) {
			for (int n = 0; n < nutrients.size(); n++) {
				ImGui::Text("Nutrient instance %.0f", nutrients[n]->
					GetComponent<Nutrient>().curEnergy);
			}
			ImGui::TreePop();
		}

		static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);

		if (ImGui::TreeNode("Background Color")) {
			ImGui::ColorEdit4("BGColor", (float*)& color);
			ImGui::TreePop();
		}

		ImGui::Separator();

		if (ImGui::Button("Add species", ImVec2(120, 25)))
			ImGui::OpenPopup("Create a new species");

		/* ----- Create new species modal|begin| ------- */
		{
			if (ImGui::BeginPopupModal("Create a new species", NULL,
				ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Enter the species' name");
				ImGui::InputText("Genus", &sGenus);
				ImGui::InputText("Epithet", &sEpithet);
				ImGui::Separator();
				if (ImGui::Button("Create", ImVec2(80, 25))) {
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
				if (ImGui::Button("Random", ImVec2(80, 25))) {

				}
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(80, 25))) {
					ImGui::CloseCurrentPopup();
					sGenus.clear();
					sEpithet.clear();
				}

				ImGui::EndPopup();
			}
		}
		/* ----- Create new species popup|end| ------- */

		ImGui::SameLine();

		if (ImGui::Button("Add nutrients", ImVec2(120, 25))) {
			Game::Get()->getEnvironment().spawnNutrients(10);
		}

		ImGui::End();
		/* ----- Environment Window|end| ------- */
	}
	
	{
		/* ----- Simulation Window|begin| ------ */
		ImGui::Begin("Simulation", NULL, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Button("Reset", ImVec2(100, 20));

		ImGui::End();
		/* ----- Simulation Window|end| -------- */
	}
	
	{
		/* ----- Debug Window|begin| --------- */
		ImGui::Begin("Debug");

		auto& entities = Game::Get()->getEntityManager().GetEntities();

		ImGui::Checkbox("Debug mode", &debugMode);

		if (ImGui::TreeNode("entitiesList", "All entities present: %i", entities.size())) {
			for (int i = 0; i < entities.size(); i++) {
				ImGui::PushID(i);

				ImGui::Text("Entity instance");

				ImGui::PopID();
			}
			ImGui::TreePop();
		}
		
		ImGui::End();
		/* ----- Debug Window|end| --------- */
	}

    imgui->End();
}

void GameGUI::OnImGuiClear() {
    imgui->Clear();
}
