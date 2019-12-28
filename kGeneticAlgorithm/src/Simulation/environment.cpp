#include "environment.h"
#include "game.h"
#include "food.h"

#include "Entities/Components.h"

/*
void Environment::addSpeciesToEnvironment(Species* species, int population, bool spawnCells)
{
	speciesInEnvironment.emplace_back(SpeciesInEnvironment{ species, population });

	LOG_INFO("Added species {} to the environment, with a population of {}",
		species->getFormattedName(true), getSpeciesPopulation(*species));

	if (spawnCells)
		spawnCell(*species, population);
}
*/

/*
void Environment::spawnCell(Species& species, int amount) {	
	for (auto& i : speciesInEnvironment) {
		if (i.species == &species) {
			for (int n = 0; n < amount; n++) {
				auto& cell(Game::GetEntityManager()->addEntity());
				auto component = cell.GetComponent<OrganismComponent>();
				cell.AddComponent<TransformComponent>(std::rand()
					% WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10,
					32, 32, 16);
				cell.AddComponent<OrganismComponent>(species);
				LOG_INFO("Cell of species: {} \n With traits: \n Aggresion: {} \n Fear: {} \n Size: {} \n Speed: {} \n Strength: {}",
					component.getSpeciesName(),
					component.getSpecies().genes.m_DNA.aggression,
					component.getSpecies().genes.m_DNA.fear,
					component.getSpecies().genes.m_DNA.size,
					component.getSpecies().genes.m_DNA.speed,
					component.getSpecies().genes.m_DNA.strength
				);
			}
		}
	}

	LOG_INFO("Spawned {} cells of species {}", amount, species.getFormattedName(true));
}
*/

void Environment::spawnFood(int amount) {
	for (int i = 0; i < amount; i++) {
		auto& food(Game::GetEntityManager()->AddEntity());
		food.AddComponent<Food>();
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
