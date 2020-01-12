#include "organism.h"

void OrganismComponent::OnInit()
{
	id = std::rand() % 20 + 1;

	// Add all of the neccesary components
	transform = &entity->AddComponent<TransformComponent>
		(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10, 10, 10, 5);
	collider = &entity->AddComponent<ColliderComponent>("organism");
	ai = &entity->AddComponent<OrganismAI>(genome->m_DNA.speed, 50);

	membraneColour = genome->m_DNA.membraneColour;
	curEnergy = genome->m_DNA.energyCapacity;
	fitness = 0;

	LOG_TRACE("{}, {}, {}", membraneColour.r, membraneColour.g, membraneColour.b);
}

void OrganismComponent::OnUpdate() {
	curEnergy -= 0.02f;
	fitness -= 0.005f;

	if (curEnergy == 0 || curEnergy < 0) {
		species->deleteOrganism(this);
	}

	if (curEnergy < 0)
		curEnergy = 0;

	if (fitness < 0)
		fitness = 0;

	if (curEnergy > genome->m_DNA.energyCapacity || fitness > 100) {
		curEnergy = genome->m_DNA.energyCapacity;
		fitness = 100;
	}
}

void OrganismComponent::OnDraw()
{
	circleShape.DrawCircle(transform->position.x, transform->position.y,
		transform->width, membraneColour, true, true);
}

std::string OrganismComponent::getSpeciesName()
{
	return species->genus + " " + species->epithet;
}

size_t OrganismComponent::getID() {
	return id;
}
