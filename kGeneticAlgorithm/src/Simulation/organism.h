#pragma once

#include "species.h"
#include "organismAI.h"

#include "Components/Components.h"
#include "PrimitiveShape.h"
#include "Collision.h"

#include <string>
#include <vector>
#include <ctime>

#include <SDL_gpu.h>

class OrganismComponent : public Component {
public:
	OrganismComponent(Species* m_species) :
		species(m_species)
	{
		genome = m_species->genes;
	}

	OrganismComponent(Species* m_species, Genes& genes) :
		species(m_species), genome(genes)
	{}

	OrganismComponent(const OrganismComponent& organism)
		: species(organism.species) {}

	~OrganismComponent() {}

	void OnInit() override;
	void OnUpdate() override;
	void OnDraw() override;

	Species* species;
	OrganismAI* ai;
	Genes genome;
	double fitness;

	std::string getSpeciesName();

	//! \todo Implement proper ID counting
	//! instead of just random numbers
	size_t getID();

	float curEnergy;

private:
	/* Components */
	PrimitiveShape circleShape;
	ColliderComponent* collider;
	TransformComponent* transform;
	SpriteComponent* sprite;

	size_t id = 0;

	SDL_Color membraneColour;
};
