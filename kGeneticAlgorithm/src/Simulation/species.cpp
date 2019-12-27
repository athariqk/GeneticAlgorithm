#include "species.h"

#include <iostream>

Species::Species(const std::string& name) : name(name) {}

Species::~Species() {}

Species* Species::_static(const std::string& name) {
	return new Species(name);
}

void Species::setPopulation(int32_t population)
{
	if (population < 0) {
		this->population = 0;
	}
	else {
		this->population = population;
	}
}

std::string Species::getFormattedName(bool identifier)
{
	std::string result;

	result = genus + " " + epithet;

	if (identifier)
		result += " (" + name + ")";

	return result;
}
