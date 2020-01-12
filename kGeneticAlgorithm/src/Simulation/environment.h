#pragma once
#include "species.h"
#include "config.h"

#include "nutrient.h"

class Environment
{
public:
	Environment() = default;
	~Environment() {}

	void addSpeciesToEnvironment(const std::string& name,
		const std::string& genus, const std::string& epithet);

	/* Spawn given amount of food to be randomly
	scattered around the environment */
	void spawnNutrients(int amount);

	void clearOrganisms();

	std::vector<Species*>& getAllSpecies();

	Species* getSpecies(const Species* species);

	Species* getSpecies(std::string name);

private:
	std::vector<Species*> speciesInEnvironment;
};

