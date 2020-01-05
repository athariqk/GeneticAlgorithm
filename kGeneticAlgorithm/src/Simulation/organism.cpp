#include "organism.h"

void OrganismComponent::OnInit()
{
	id = std::rand() % 20 + 1;

	// Add neccesary components
	transform = &entity->AddComponent<TransformComponent>
		(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10, 10, 10, 5);

	collider = &entity->AddComponent<ColliderComponent>("organism");

	ai = &entity->AddComponent<OrganismAI>(1, 50);
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

size_t OrganismComponent::getID() {
	return id;
}
