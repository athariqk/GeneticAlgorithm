#include "species.h"
#include "organism.h"
#include "game.h"

#include "Simulation/environment.h"

#include <iostream>

Species::Species(const std::string& name, const std::string& genus,
	const std::string& epithet) :
	name(name),
	genus(genus),
	epithet(epithet)
{}

void Species::addOrganism()
{
	auto& instance(Game::Get()->getEntityManager().AddEntity());
	instance.AddComponent<OrganismComponent>(&genes);
	organisms.push_back(&instance.GetComponent<OrganismComponent>());

	LOG_INFO("Added organism of species {}, Population: {}",
		getFormattedName(false), getPopulationCount());
}

size_t Species::getPopulationCount() const
{
	return organisms.size();
}

std::vector<OrganismComponent*>& Species::getOrganisms()
{
	return organisms;
}

std::string Species::getFormattedName(bool identifier)
{
	std::string result;

	result = genus + " " + epithet;

	if (identifier)
		result += " (" + name + ")";

	return result;
}

size_t Species::getID() {
	return id;
}
