#pragma once
#include "population.h"
#include "genes.h"

#include "Entities/Components.h"

#include <string>
#include <vector>

class OrganismComponent;

class Species : public Component
{
public:
	Species() = default;
	Species(const std::string& name, const std::string& genus,
		const std::string& epithet);
	~Species() {}

	void addOrganism();

	size_t getPopulationCount() const;

	size_t getID();

	std::string getFormattedName(bool identifier);

	std::vector<OrganismComponent*>& getOrganisms();

	int age;
	double averageFitness;
	double maxFitness;
	double maxFitnessEver;

	std::string name;
	std::string genus;
	std::string epithet;

	Genes genes;

	int32_t generation;

private:
	//! \todo Maybe hold vector of entities instead?
	std::vector<OrganismComponent*> organisms;

	size_t id;
};

