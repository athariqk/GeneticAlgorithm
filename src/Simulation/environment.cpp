#include "environment.h"

#include "scene.h"
#include "nutrient.h"
#include "organism.h"

#include "Logger.h"

void Environment::addSpeciesToEnvironment(const std::string& name,
	const std::string& genus, const std::string& epithet)
{
	auto& instance(Scene::Get()->GetEntityManager().AddEntity());
	instance.AddComponent<Species>(name, genus, epithet);
	speciesInEnvironment.push_back(&instance.GetComponent<Species>());

	auto& species = instance.GetComponent<Species>();

	LOG_INFO("Added species {} to the environment, with following traits:\n speed {}, energy capacity {}, size {}",
		species.getFormattedName(true),
		species.genes.speed,
		species.genes.energyCapacity,
		species.genes.size);

	species.addOrganism();
}

Species* Environment::getSpecies(const Species* species) {
	for (auto& s : speciesInEnvironment) {
		if (s == species)
			return s;
	}

	LOG_ERROR("Species is not found!");
	return nullptr;
}

Species* Environment::getSpecies(std::string name) {
	for (auto& s : speciesInEnvironment) {
		if (s->name == name) {
			return s;
		}
	}

	LOG_ERROR("Not found species with name {}", name);
	return nullptr;
}

std::vector<Species*>& Environment::getAllSpecies()
{
	return speciesInEnvironment;
}

void Environment::makeExtinct(Species* species) {
	for (auto& it : speciesInEnvironment) {
		if (it == species) {
			it->entity->Destroy();
			speciesInEnvironment.erase(speciesInEnvironment.begin()
				+ getSpeciesIndex(species));

			/* Clear the population */
			it->clearOrganisms();

			LOG_INFO("Species {} has gone extinct!",
				species->getFormattedName(false));
		}
	}
}

int Environment::getSpeciesIndex(Species* species) {
	std::vector<Species*>::iterator it =
		std::find(speciesInEnvironment.begin(),speciesInEnvironment.end(), species);

	if (it != speciesInEnvironment.end()) {
		return std::distance(speciesInEnvironment.begin(), it);
	}
	else {
		LOG_ERROR("Index of species {} is not found!", species->getID());
		return NULL;
	}
}

void Environment::spawnNutrients(int amount) {
    for (int i = 0; i < amount; i++) {
        auto& nutrient(Scene::Get()->GetEntityManager().AddEntity());
        nutrient.AddComponent<Nutrient>(30);
		nutrient.AddGroup(Scene::groupLabels::NutrientsGroup);
    }
	LOG_INFO("Spawned {} nutrients to the environment", amount);
}
