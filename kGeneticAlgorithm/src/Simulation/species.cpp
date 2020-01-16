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

void Species::OnUpdate() {
	if (organisms.empty()) {
		Game::Get()->getEnvironment().makeExtinct(this);
	}
}

void Species::addOrganism()
{
	auto& instance(Game::Get()->getEntityManager().AddEntity());
	instance.AddComponent<OrganismComponent>(this);
	organisms.push_back(&instance.GetComponent<OrganismComponent>());

	auto& organism = instance.GetComponent<OrganismComponent>();

	LOG_INFO("Added organism of species {}, ID: {} with following "
		"traits:\n energy cap {}, speed {}, size {}, aggresiveness {}",
		getFormattedName(false), organism.getID(),
		organism.genome.energyCapacity,
		organism.genome.speed,
		organism.genome.size,
		organism.genome.aggresiveness);
}

void Species::addOrganism(Genes& genes, bool mutate) {
	auto& instance(Game::Get()->getEntityManager().AddEntity());
	instance.AddComponent<OrganismComponent>(this, genes);
	organisms.push_back(&instance.GetComponent<OrganismComponent>());

	auto& organism = instance.GetComponent<OrganismComponent>();

	// Do random mutations
	if (mutate) {
		if (organism.genome.mutate(5, 1)) {
			LOG_INFO("Mutation occured on organism {}",
				organism.getID());
		}
	}

	LOG_INFO("Added organism of species {}, ID: {} with following "
		"traits:\n energy cap {}, speed {}, size {}, aggresiveness {}",
		getFormattedName(false), organism.getID(),
		organism.genome.energyCapacity,
		organism.genome.speed,
		organism.genome.size,
		organism.genome.aggresiveness);
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

void Species::clearOrganisms() {
	/* Proceed if not empty */
	if (!organisms.empty()) {
		for (auto& it : organisms)
			it->entity->Destroy();

		organisms.clear();
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
