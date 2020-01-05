#pragma once

#include "species.h"
#include "organismAI.h"

#include "Entities/Components.h"
#include "PrimitiveShape.h"
#include "Collision.h"

#include <string>
#include <vector>
#include <ctime>

#include <SDL_gpu.h>

class Species;

class OrganismComponent : public Component {
public:
	// Temporary
	OrganismComponent(float initialEnergy) :
		energy(initialEnergy) {}

	OrganismComponent(double m_fitness, Genes* gene)
		: fitness(m_fitness), genome(gene) {}

	OrganismComponent(const OrganismComponent& organism)
		: species(organism.species) {}

	~OrganismComponent() {}

	void OnInit() override;
	void OnDraw() override;

	// For GA use
	Species* species;
	Genes* genome;
	double fitness;

	float energy;

	std::string getSpeciesName();

	//! \todo Implement real ID counting
	//! instead of just random numbers
	size_t getID();

private:
	PrimitiveShape circleShape;
	
	ColliderComponent* collider;
	TransformComponent* transform;
	SpriteComponent* sprite;
	OrganismAI* ai;

	size_t id = 0;
};
