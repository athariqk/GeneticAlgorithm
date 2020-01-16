#pragma once
#include "genes.h"

#include "Components/Components.h"

#include <string>
#include <vector>

class OrganismComponent;

/**
 * Equivalent to a GA Population operator
 */
class Species : public Component
{
public:
	Species() = default;
	Species(const std::string& name, const std::string& genus,
		const std::string& epithet);
	~Species() {}

	void OnUpdate() override;

	//! \brief Spawn a single organism
	void addOrganism();

	//! \brief Spawn a single organism with given genes
	//! and randomly mutate it if set true
	void addOrganism(Genes& genes, bool mutate);

	//! \brief Destroy a single given organism
	void deleteOrganism(OrganismComponent* organism);

	//! \brief Destroy all members of this species
	void clearOrganisms();

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

