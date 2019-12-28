#pragma once
#include "population.h"
#include "genes.h"
#include "organism.h"

#include "Entities/Components.h"

#include <stdint.h>
#include <string>
#include <vector>

class Species : Component
{
public:
	Species() = default;
	Species(const std::string& name, const std::string& genus,
		const std::string& epithet);
	~Species();

	size_t GetID();

	//void setPopulation(int32_t population);

	bool addOrganism(OrganismComponent* organism);

	bool removeOrganism(OrganismComponent* organism);

	bool reproduce(uint64_t generation, Population* population,
		std::vector<Species*> sortedSpecies);

	bool sortFitness();

	int age;
	double averageFitness;
	double maxFitness;
	double maxFitnessEver;

	std::vector<OrganismComponent*> organisms;

	std::string getFormattedName(bool identifier);

	std::string name;
	std::string genus;
	std::string epithet;

	Genes genes;

	bool finished;

	int32_t population;

	int32_t generation;

private:
	size_t incrementor;
};

