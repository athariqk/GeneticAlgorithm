#include "environment.h"
#include "game.h"
#include "food.h"

#include "Entities/Components.h"

Species Environment::createSpecies(const std::string & name, const std::string & genus,
	const std::string epithet, float aggression, float fear, float size, float speed)
{
	Species species = Species(name);

	species.genus = genus;
	species.epithet = epithet;
	species.aggression = aggression;
	species.fear = fear;
	species.size = size;
	species.speed = speed;

	return species;
}

void Environment::addSpeciesToEnvironment(Species* species, int population, bool spawnCells)
{
	speciesInEnvironment.emplace_back(SpeciesInEnvironment{ species, population });

	LOG_INFO("Added species {} to the environment, with a population of {}",
		species->getFormattedName(true), getSpeciesPopulation(*species));

	if (spawnCells)
		spawnCell(*species, population);
}

void Environment::spawnCell(Species& species, int amount) {	
	for (auto& i : speciesInEnvironment) {
		if (i.species == &species) {
			for (int n = 0; n < amount; n++) {
				auto& cell(Game::GetEntityManager()->addEntity());
				cell.AddComponent<TransformComponent>(std::rand()
					% WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10);
				cell.AddComponent<MicrobeComponent>(species);
			}
		}
	}

	LOG_INFO("Spawned {} cells of species {}", amount, species.getFormattedName(true));
}

void Environment::spawnFood(int amount) {
	for (int i = 0; i < amount; i++) {
		auto& food(Game::GetEntityManager()->addEntity());
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
