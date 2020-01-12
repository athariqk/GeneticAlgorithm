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
	instance.AddComponent<OrganismComponent>(this);
	organisms.push_back(&instance.GetComponent<OrganismComponent>());

	LOG_INFO("Added organism of species {}, Population: {} with following traits: energy {}, speed {}",
		getFormattedName(false), getPopulationCount(),
		organisms.back()->genome->m_DNA.energyCapacity,
		organisms.back()->genome->m_DNA.speed);
}

void Species::deleteOrganism(OrganismComponent* organism)
{
	for (auto& it : organisms) {
		if (it == organism) {
			it->entity->Destroy();
			organisms.erase(organisms.begin() + getOrganismIndex(organism));
		}
	}
}

int Species::getOrganismIndex(OrganismComponent* organism) {
	std::vector<OrganismComponent*>::iterator it =
		std::find(organisms.begin(), organisms.end(), organism);

	if (it != organisms.end()) {
		return std::distance(organisms.begin(), it);
	}
	else {
		LOG_ERROR("Index of organism {} is not found!", organism->getID());
		return NULL;
	}
}

size_t Species::getPopulationCount() {
	return organisms.size();
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
