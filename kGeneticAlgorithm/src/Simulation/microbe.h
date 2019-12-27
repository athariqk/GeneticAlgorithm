#pragma once

#include "species.h"
#include "microbe_ai.h"

#include "Entities/Components.h"
#include "PrimitiveShape.h"

#include <string>

class Species;

class MicrobeComponent : public Component
{
public:
	MicrobeComponent(Species species) :
		cellSpecies(species), usePrimitiveShape(true) {}
	MicrobeComponent(Species species, const char* texturePath) :
		cellSpecies(species), texture(texturePath) {}

	~MicrobeComponent() {}

	void OnInit() override {
		transform = &entity->GetComponent<TransformComponent>();

		if(!usePrimitiveShape)
			sprite = &entity->AddComponent<SpriteComponent>(texture);

		ai = &entity->AddComponent<MicrobeAI>();
	}

	void OnDraw() override {
		if (usePrimitiveShape) {
			shape.DrawCircle(transform->position.x, transform->position.y, 10);
		}
	}

	std::string getCellSpeciesName() {
		return cellSpecies.genus + " " + cellSpecies.epithet;
	}

private:
	Species cellSpecies;

	MicrobeAI* ai;
	TransformComponent* transform;
	SpriteComponent* sprite;
	PrimitiveShape shape;
	const char* texture;

	bool usePrimitiveShape = false;
};

