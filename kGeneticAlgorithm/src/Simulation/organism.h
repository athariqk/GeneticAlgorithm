#pragma once

#include "species.h"

#include "Entities/Components.h"
#include "PrimitiveShape.h"
#include "Collision.h"

#include <string>
#include <vector>
#include <ctime>

class Species;

class OrganismComponent : public Component {
public:
    OrganismComponent() : usePrimitiveShape(true) {}
    // The organism would later be created somewhere in
    // the evolution algorithm
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
        transform = &entity->AddComponent<TransformComponent>();
        collider = &entity->AddComponent<ColliderComponent>("organism");
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
        // Linear interpolation from current position -> nutrient position
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
    PrimitiveShape shape;
    const char* texture;

    int index;

    bool usePrimitiveShape = false;
};
