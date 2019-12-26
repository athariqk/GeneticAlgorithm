#pragma once

#include <stdint.h>
#include <string>
#include <vector>

class Species
{
public:
	Species() = default;
	Species(const std::string& name);
	~Species();

	void setPopulation(int32_t population);

	std::string getFormattedName(bool identifier);

	static Species* _static(const std::string& name);

	std::string name;
	std::string genus;
	std::string epithet;

	float aggression = 100.0f;
	float fear = 100.0f;
	float size = 10.0f;
	float speed = 5.0f;
	float strength = 10.0f;

	float mutationRate = 1.0f;

	bool finished;

	int32_t population;

	int32_t generation;
};

