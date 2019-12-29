#pragma once
#include "organism.h"
#include "species.h"
#include "config.h"

#include <vector>

//! \note This class is probably not needed.

class Environment
{
public:
	struct SpeciesInEnvironment {
		Species* species;
		int population = 0;
	};

	//! \note A species has to be created first!
	//void addSpeciesToEnvironment(Species* species,
	//	int population = INITIAL_SPECIES_POPULATION, bool spawnCells = false);

	// Spawn cell of a given species randomly
	// around the environment
	//void spawnCell(Species& species, int amount);

	// Spawn given amount of food to be randomly
	// scattered around the environment
	void spawnNutrients(int amount);

	Species* getSpecies(uint64_t index);

	int getSpeciesPopulation(const Species& species);

	// Return amount of all species in the environment
	uint64_t getSpeciesCount();

private:
	std::vector<SpeciesInEnvironment> speciesInEnvironment;
};

