#include "environment.h"
#include "game.h"
#include "nutrient.h"

#include "Entities/Components.h"

void Environment::spawnNutrients(int amount) {
    for (int i = 0; i < amount; i++) {
        auto& nutrient(Game::GetEntityManager()->AddEntity());
        nutrient.AddComponent<Nutrient>(10);
		nutrient.AddGroup(Game::groupLabels::Nutrients);
    }
}

Species* Environment::getSpecies(uint64_t index) {
	if (index >= speciesInEnvironment.size())
		return nullptr;

	return speciesInEnvironment[index].species;
}

int Environment::getSpeciesPopulation(const Species& species) {
	for (auto& i : speciesInEnvironment) {
		if (i.species == &species) {
			return i.population;
		}
	}

	return 0;
}

uint64_t Environment::getSpeciesCount() {
	return speciesInEnvironment.size();
}
