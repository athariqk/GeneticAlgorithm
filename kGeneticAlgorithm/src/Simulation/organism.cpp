#include "organism.h"
#include "game.h"
#include "gameGUI.h"

void OrganismComponent::OnInit()
{
	id = std::rand() % 20 + 1;

	// Add all of the neccesary components
	transform = &entity->AddComponent<TransformComponent>
		(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10,
			genome.size, genome.size, genome.size);

	collider = &entity->AddComponent<ColliderComponent>("organism");
	ai = &entity->AddComponent<OrganismAI>(genome.speed, 50);

	membraneColour = genome.membraneColour;
	curEnergy = genome.energyCapacity;
	fitness = 0;
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

	if (curEnergy > genome.energyCapacity || fitness > 100) {
		curEnergy = genome.energyCapacity;
		fitness = 100;
	}

	if (Game::Get()->getGUI().debugMode) {
		collider->debug = true;
	}
	else {
		collider->debug = false;
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
