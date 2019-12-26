#pragma once

#include "species.h"

#include "Components.h"

#include <string>

class Species;

class MicrobeComponent : public Component
{
public:
	MicrobeComponent(Species species, const char* texturePath) :
		cellSpecies(species), texture(texturePath) {}

	~MicrobeComponent() {}

	void Init() override {
		transform = &entity->GetComponent<TransformComponent>();
		sprite = &entity->AddComponent<SpriteComponent>(texture);
	}

	Species cellSpecies;

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	const char* texture;
};

