#include "environment.h"
#include "game.h"
#include "nutrient.h"

#include "organism.h"

#include "Entities/Components.h"

void Environment::addSpeciesToEnvironment(const std::string& name,
	const std::string& genus, const std::string& epithet)
{
	auto& instance(Game::Get()->getEntityManager().AddEntity());
	instance.AddComponent<Species>(name, genus, epithet);
	speciesInEnvironment.push_back(&instance.GetComponent<Species>());

	LOG_INFO("Added species {} to the environment, with following traits: speed {}, energy capacity {}",
		instance.GetComponent<Species>().getFormattedName(true),
		instance.GetComponent<Species>().genes.m_DNA.speed,
		instance.GetComponent<Species>().genes.m_DNA.energyCapacity
	);
}

Species* Environment::getSpecies(const Species* species) {
	for (auto& s : speciesInEnvironment) {
		if (s == species)
			return s;
	}
}

Species* Environment::getSpecies(std::string name) {
	for (auto& s : speciesInEnvironment) {
		if (s->name == name) {
			return s;
		}
	}
}

std::vector<Species*>& Environment::getAllSpecies()
{
	return speciesInEnvironment;
}

void Environment::clearOrganisms() {
	auto& group(Game::Get()->getEntityManager().
		GetGroup(Game::groupLabels::OrganismsGroup));

	if (!group.empty())
		for (auto& e : group) {
			e->Destroy();
		}
}

void Environment::spawnNutrients(int amount) {
    for (int i = 0; i < amount; i++) {
        auto& nutrient(Game::Get()->getEntityManager().AddEntity());
        nutrient.AddComponent<Nutrient>(30);
		nutrient.AddGroup(Game::groupLabels::NutrientsGroup);
    }
	LOG_INFO("Spawned {} nutrients to the environment", amount);
}
