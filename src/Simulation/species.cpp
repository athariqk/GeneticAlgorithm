#include "species.h"
#include "organism.h"
#include "scene.h"

#include "Simulation/environment.h"
#include "Engine/AudioManager.h"

#include "Logger.h"

#include <iostream>

Species::Species(const std::string& name, const std::string& genus,
                 const std::string& epithet) :
	name(name),
	genus(genus),
	epithet(epithet)
{}

void Species::OnUpdate(float delta) {
	if (organisms.empty()) {
		Scene::Get()->GetEnvironment().makeExtinct(this);
	}
}

void Species::addOrganism()
{
	auto& instance(Scene::Get()->GetEntityManager().AddEntity());
	instance.AddComponent<OrganismComponent>(this);
	organisms.push_back(&instance.GetComponent<OrganismComponent>());

	auto& organism = instance.GetComponent<OrganismComponent>();

	LOG_INFO("Added organism of species {}, ID: {} with following "
		"traits:\n energy cap {}, speed {}, size {}, aggressiveness {}",
		getFormattedName(false), organism.getID(),
		organism.genome.energyCapacity,
		organism.genome.speed,
		organism.genome.size,
		organism.genome.aggresiveness);

	Scene::Get()->GetAudio().PlayWAV("assets/pop.wav");
}

void Species::addOrganism(Genes& genes, const bool mutate) {
	auto& instance(Scene::Get()->GetEntityManager().AddEntity());
	instance.AddComponent<OrganismComponent>(this, genes);
	organisms.push_back(&instance.GetComponent<OrganismComponent>());

	auto& organism = instance.GetComponent<OrganismComponent>();

	// Do random mutations
	if (mutate) {
		if (organism.genome.mutate(5, 1)) {
			LOG_INFO("Mutation occurred on organism {}",
				organism.getID());
		}
	}

	LOG_INFO("Added organism of species {}, ID: {} with following "
		"traits:\n energy cap {}, speed {}, size {}, aggressiveness {}",
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
	if (const auto it = std::ranges::find(organisms, organism); it != organisms.end()) {
		return std::distance(organisms.begin(), it);
	}

	LOG_ERROR("Index of organism {} is not found!", organism->getID());
	return -1;
}

size_t Species::getPopulationCount() const {
	return organisms.size();
}

std::string Species::getFormattedName(const bool identifier) const {
	std::string result = genus + " " + epithet;

	if (identifier)
		result += " (" + name + ")";

	return result;
}

size_t Species::getID() const {
	return id;
}
