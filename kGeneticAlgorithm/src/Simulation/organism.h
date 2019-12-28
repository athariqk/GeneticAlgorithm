#pragma once

#include "species.h"
#include "organism_ai.h"
#include "genes.h"

#include "Entities/Components.h"
#include "PrimitiveShape.h"

#include <string>

class Species;

class OrganismComponent : public Component
{
public:
	// The organism would be created somewhere in
	// the evolution algorithm
	OrganismComponent(double m_fitness, Genes* gene) :
		fitness(m_fitness), genome(gene), usePrimitiveShape(true)
	{}

	OrganismComponent(const OrganismComponent& organism) :
		species(organism.species), usePrimitiveShape(true)
	{}

	OrganismComponent(Species species, const char* texturePath) :
		species(&species), texture(texturePath)
	{}

	~OrganismComponent() {}

	void OnInit() override {
		transform = &entity->GetComponent<TransformComponent>();

		if(!usePrimitiveShape)
			sprite = &entity->AddComponent<SpriteComponent>(texture);

		ai = &entity->AddComponent<OrganismAI>();
	}

	void OnDraw() override {
		if (usePrimitiveShape) {
			shape.DrawCircle(transform->position.x, transform->position.y, 10);
		}
	}

	std::string getSpeciesName() {
		return species->genus + " " + species->epithet;
	}

	Species* species;

	Genes* genome;

	double fitness;

private:
	OrganismAI* ai;
	TransformComponent* transform;
	SpriteComponent* sprite;
	PrimitiveShape shape;
	const char* texture;

	bool usePrimitiveShape = false;
};

