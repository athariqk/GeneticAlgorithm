#include "organism.h"

void OrganismComponent::OnInit()
{
	id = std::rand() % 20 + 1;

	// Add all of the neccesary components
	transform = &entity->AddComponent<TransformComponent>
		(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10, 10, 10, 5);
	collider = &entity->AddComponent<ColliderComponent>("organism");
	ai = &entity->AddComponent<OrganismAI>(1, 50);

	fitness = 0;
}

void OrganismComponent::OnUpdate() {
	curEnergy -= 0.02f;
	fitness -= 0.005f;

	if (curEnergy == 0) {
		entity->Destroy();
	}

	if (curEnergy < 0 || fitness < 0) {
		curEnergy = 0;
		fitness = 0;
	}

	if (curEnergy > genome->m_DNA.energyCapacity || fitness > 100) {
		curEnergy = genome->m_DNA.energyCapacity;
		fitness = 100;
	}
}

void OrganismComponent::OnDraw()
{
	circleShape.DrawCircle(transform->position.x,
		transform->position.y, transform->width);
}

std::string OrganismComponent::getSpeciesName()
{
	return species->genus + " " + species->epithet;
}

OrganismAI* OrganismComponent::getAI()
{
	return ai;
}

size_t OrganismComponent::getID() {
	return id;
}
