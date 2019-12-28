#include "species.h"
#include "game.h"

#include <iostream>

Species::Species(const std::string& name,
	const std::string& genus, const std::string& epithet) :
	name(name),
	genus(genus),
	epithet(epithet)
{}

Species::~Species() {}

bool Species::addOrganism(OrganismComponent* organism) {
	auto& m_org(Game::GetEntityManager()->AddEntity());
	m_org.AddComponent<OrganismComponent>(organism);
	m_org.AddGroup(1);
	return true;
}

/*
void Species::setPopulation(int32_t population)
{
	if (population < 0) {
		this->population = 0;
	}
	else {
		this->population = population;
	}
}
*/

std::string Species::getFormattedName(bool identifier)
{
	std::string result;

	result = genus + " " + epithet;

	if (identifier)
		result += " (" + name + ")";

	return result;
}

size_t Species::GetID() {
	return incrementor++;
}
