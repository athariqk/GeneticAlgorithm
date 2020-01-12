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
	void deleteOrganism(OrganismComponent* organism);
	size_t getID();
	size_t getPopulationCount();
	int getOrganismIndex(OrganismComponent* organism);
	std::string getFormattedName(bool identifier);
	std::vector<OrganismComponent*> organisms;

	int age;

	std::string name;
	std::string genus;
	std::string epithet;

	Genes genes;
	int32_t generation;

private:
	size_t id;
};

