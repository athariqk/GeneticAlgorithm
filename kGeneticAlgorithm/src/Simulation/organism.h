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

class OrganismComponent : public Component {
public:
	OrganismComponent(Genes* gene) :
		genome(gene)
	{}

	OrganismComponent(const OrganismComponent& organism)
		: species(organism.species) {}

	~OrganismComponent() {}

	void OnInit() override;
	void OnUpdate() override;
	void OnDraw() override;

	// For GA purposes
	Species* species;
	Genes* genome;
	double fitness;

	std::string getSpeciesName();

	OrganismAI* getAI();

	//! \todo Implement real ID counting
	//! instead of just random numbers
	size_t getID();

	float curEnergy;

private:
	// Components
	PrimitiveShape circleShape;
	ColliderComponent* collider;
	TransformComponent* transform;
	SpriteComponent* sprite;
	OrganismAI* ai;

	size_t id = 0;
};
