#pragma once
#include "microbe.h"
#include "species.h"
#include "config.h"

#include <vector>

class Environment
{
public:
	Environment();
	~Environment();

	struct SpeciesInEnvironment {
		Species* species;
		int population = 0;
	};

	Species createSpecies(const std::string & name, const std::string & genus,
		const std::string epithet, float aggression, float fear, float size, float speed);

	void addSpeciesToEnvironment(Species* species,
		int population = INITIAL_SPECIES_POPULATION, bool spawnCells = false);

	void spawnCell(Species& species, int amount);

	Species* getSpecies(uint64_t index);

	int getSpeciesPopulation(const Species& species);

	uint64_t getSpeciesCount();

private:
	std::vector<SpeciesInEnvironment> speciesInEnvironment;
};

