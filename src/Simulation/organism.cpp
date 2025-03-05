#include "organism.h"

#include "Camera.h"
#include "organismAI.h"
#include "species.h"

#include "Components/RigidBodyComponent.h"
#include "Components/TransformComponent.h"
#include "PrimitiveShape.h"
#include "Random.h"

OrganismComponent::OrganismComponent(Species *m_species) : species(m_species) { genome = m_species->genes; }

void OrganismComponent::OnInit() {
    id = Random::RandomInt(0, 20);

    const auto &camera = Scene::GetCamera();
    float spawnX = camera.position.x + Random::RandomFloat(-100, 100);
    float spawnY = camera.position.y + Random::RandomFloat(-100, 100);

    // Add all the necessary components
    transform = &entity->AddComponent<TransformComponent>(spawnX, spawnY, genome.size, genome.size);
    rb = &entity->AddComponent<RigidBodyComponent>();
    ai = &entity->AddComponent<OrganismAI>(genome.speed, 50);

    membraneColour = genome.membraneColour;
    curEnergy = genome.energyCapacity;
    fitness = 0;
}

void OrganismComponent::OnUpdate(float delta) {
    curEnergy -= 0.02f;
    fitness -= 0.005f;

    if (curEnergy == 0 || curEnergy < 0) {
        species->deleteOrganism(this);
    }

    if (curEnergy < 0)
        curEnergy = 0;

    if (fitness < 0)
        fitness = 0;

    if (curEnergy > genome.energyCapacity || fitness > 100) {
        curEnergy = genome.energyCapacity;
        fitness = 100;
    }
}

void OrganismComponent::OnDraw() {
    const auto pos = transform->GetScreenPosition();
    PrimitiveShape::DrawCircle(pos.x, pos.y, transform->width / 2, membraneColour, true, true);
}

std::string OrganismComponent::getSpeciesName() const { return species->genus + " " + species->epithet; }

size_t OrganismComponent::getID() const { return id; }
