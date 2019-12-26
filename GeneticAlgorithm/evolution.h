#pragma once

#include "species.h"
#include "config.h"

#include <vector>
#include <stdint.h>

class DNA {
public:
	struct Genes {
		float speed;
		float strength;
		float size;
	};

	std::vector<Genes> genes;

	float fitness;
};

struct Individual {
	std::vector<DNA> dna = std::vector<DNA>(MAX_POPULATION);
	int fitness;
};

struct Population {
	std::vector<Individual> individual = std::vector<Individual>(MAX_POPULATION);
};

class Evolution
{
public:
	Evolution();
	~Evolution();

	Species createSpecies(const std::string& name, const std::string& genus,
		const std::string& epithet, float aggression, float fear);

	static Evolution* Get();

private:
	static Evolution* staticEvolution;
};
