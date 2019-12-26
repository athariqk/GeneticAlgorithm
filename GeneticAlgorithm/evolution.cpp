#include "evolution.h"

Evolution* Evolution::staticEvolution;

Evolution::Evolution()
{
	staticEvolution = this;
}


Evolution::~Evolution()
{
	staticEvolution = nullptr;
}

Evolution*
	Evolution::Get()
{
	return staticEvolution;
}

Species Evolution::createSpecies(const std::string & name, const std::string & genus,
	const std::string & epithet, float aggression, float fear)
{
	Species species = Species(name);

	species.genus = genus;
	species.epithet = epithet;
	species.aggression = aggression;
	species.fear = fear;

	return species;
}

