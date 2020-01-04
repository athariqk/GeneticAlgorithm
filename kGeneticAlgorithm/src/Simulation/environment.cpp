#include "environment.h"
#include "game.h"
#include "nutrient.h"

#include "Entities/Components.h"

void Environment::addSpeciesToEnvironment(const std::string& name,
	const std::string& genus, const std::string& epithet)
{
	auto& speciesInstance(Game::Get()->getEntityManager().AddEntity());
	speciesInstance.AddComponent<Species>(name, genus, epithet);
	speciesInstance.AddGroup(Game::groupLabels::SpeciesGroup);
	LOG_INFO("Added species {} to the environment",
		speciesInstance.GetComponent<Species>().getFormattedName(true));
}

Species* Environment::getSpecies(const Species* species) {
	auto& m_species(Game::Get()->getEntityManager().
		GetGroup(Game::groupLabels::SpeciesGroup));

	for (auto& i : m_species) {
		if (&i->GetComponent<Species>() == species) {
			return &i->GetComponent<Species>();
		}
	}
}

uint64_t Environment::getSpeciesCount() const {
	auto& m_species(Game::Get()->getEntityManager().
		GetGroup(Game::groupLabels::SpeciesGroup));

	return m_species.size();
}

void Environment::spawnNutrients(int amount) {
    for (int i = 0; i < amount; i++) {
        auto& nutrient(Game::Get()->getEntityManager().AddEntity());
        nutrient.AddComponent<Nutrient>(10);
		nutrient.AddGroup(Game::groupLabels::NutrientsGroup);
    }
}
