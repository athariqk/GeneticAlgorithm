#pragma once

#include "species.h"

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
    OrganismComponent() : usePrimitiveShape(true) {}

    OrganismComponent(double m_fitness, Genes* gene)
        : fitness(m_fitness), genome(gene), usePrimitiveShape(true) {}

    OrganismComponent(const OrganismComponent& organism)
        : species(organism.species), usePrimitiveShape(true) {}

    //OrganismComponent(Species species, const char* texturePath) :
    //	species(&species), texture(texturePath)
    //{}

    ~OrganismComponent() {}

    Species* species;

    Genes* genome;

    double fitness;

    void OnInit() override
    {
        index = std::rand() % 20 + 0;
        transform = &entity->AddComponent<TransformComponent>
			(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10, 10);

        collider = &entity->AddComponent<ColliderComponent>("organism");

        if (!usePrimitiveShape)
            sprite = &entity->AddComponent<SpriteComponent>(texture);

        nutrients = Game::GetEntityManager()->GetGroup(Game::groupLabels::Nutrients);
    }

    void OnDraw() override
    {
        if (usePrimitiveShape) {
            PrimitiveShape::DrawCircle(transform->position.x,
				transform->position.y, transform->scale);
        }
    }

    void OnUpdate() override
    {
        // Linear interpolation from initial position -> nutrient position
        transform->position = transform->position.Lerp(transform->position,
            nutrients.at(index)->GetComponent<TransformComponent>().position, 0.01f);
    }

    std::string getSpeciesName()
    {
        return species->genus + " " + species->epithet;
    }

private:
    std::vector<Entity*> nutrients;

	ColliderComponent* collider;
    TransformComponent* transform;
    SpriteComponent* sprite;
    //PrimitiveShape shape;
    const char* texture;

    int index;

    bool usePrimitiveShape = false;
};
