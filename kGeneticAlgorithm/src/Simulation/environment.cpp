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
	instance.AddGroup(Game::groupLabels::SpeciesGroup);
	LOG_INFO("Added species {} to the environment",
		instance.GetComponent<Species>().getFormattedName(true));
}

void Environment::addOrganismToEnvironment() {
	auto& instance(Game::Get()->getEntityManager().AddEntity());
	instance.AddComponent<OrganismComponent>(100);
	instance.AddGroup(Game::groupLabels::OrganismsGroup);
	LOG_INFO("Added organism {} to the environment",
		instance.GetComponent<OrganismComponent>().getID());
}

void Environment::clearOrganisms() {
	auto& group(Game::Get()->getEntityManager().
		GetGroup(Game::groupLabels::OrganismsGroup));

	if (!group.empty())
		for (auto& e : group) {
			e->Destroy();
		}
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
