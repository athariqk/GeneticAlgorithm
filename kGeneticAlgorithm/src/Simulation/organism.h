#pragma once

#include "species.h"

#include "Entities/Components.h"
#include "PrimitiveShape.h"

#include <string>
#include <iterator>
#include <vector>
#include <random>
#include <ctime>

class Species;

class OrganismComponent : public Component {
public:
    OrganismComponent() : usePrimitiveShape(true) {}
    // The organism would be created somewhere in
    // the evolution algorithm
    OrganismComponent(double m_fitness, Genes* gene) :
		fitness(m_fitness), genome(gene), usePrimitiveShape(true) {}

    OrganismComponent(const OrganismComponent& organism) :
		species(organism.species), usePrimitiveShape(true) {}

    //OrganismComponent(Species species, const char* texturePath) :
    //	species(&species), texture(texturePath)
    //{}

    ~OrganismComponent() {}

    Species* species;

    Genes* genome;

    double fitness;

	int index;

    void OnInit() override
    {
        index = std::rand() % 10 + 0;
        transform = &entity->AddComponent<TransformComponent>();

        if (!usePrimitiveShape)
            sprite = &entity->AddComponent<SpriteComponent>(texture);

		nutrients = Game::GetEntityManager()->GetGroup(Game::groupLabels::Nutrients);
    }

    void OnDraw() override
    {
        if (usePrimitiveShape) {
            shape.DrawCircle(transform->position.x, transform->position.y, 10);
        }
    }

    void OnUpdate() override
    {
        transform->position = transform->position.Lerp(transform->position,
            nutrients.at(index)->GetComponent<TransformComponent>().position, 0.01f);
    }

    std::string getSpeciesName()
    {
        return species->genus + " " + species->epithet;
    }

private:
    std::vector<Entity*> nutrients;
    TransformComponent* transform;
    SpriteComponent* sprite;
    PrimitiveShape shape;
    const char* texture;

    bool usePrimitiveShape = false;
};
