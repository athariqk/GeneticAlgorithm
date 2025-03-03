#include "organism.h"

#include "species.h"
#include "organismAI.h"

#include "PrimitiveShape.h"
#include "Components/TransformComponent.h"
#include "Components/RigidBodyComponent.h"

#include "config.h"

OrganismComponent::OrganismComponent(Species *m_species) : species(m_species) {
	genome = m_species->genes;
}


void OrganismComponent::OnInit() {
	id = std::rand() % 20 + 1;

	// Add all the necessary components
	transform = &entity->AddComponent<TransformComponent>
	(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10,
	 genome.size, genome.size);
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
	auto pos = transform->GetScreenPosition();
	PrimitiveShape::DrawCircle(pos.x, pos.y, transform->width / 2, membraneColour, true, true);
}

std::string OrganismComponent::getSpeciesName() const {
	return species->genus + " " + species->epithet;
}

size_t OrganismComponent::getID() const {
	return id;
}
