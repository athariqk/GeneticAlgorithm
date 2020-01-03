#include "organism.h"

void OrganismComponent::OnInit()
{
	// Add transform and collider components first
	transform = &entity->AddComponent<TransformComponent>
		(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10, 10);
	collider = &entity->AddComponent<ColliderComponent>("organism");
	ai = &entity->AddComponent<OrganismAI>(1, 50, 50);
}

void OrganismComponent::OnDraw()
{
	PrimitiveShape::DrawCircle(transform->position.x,
		transform->position.y, transform->scale);
}

std::string OrganismComponent::getSpeciesName()
{
	return species->genus + " " + species->epithet;
}

size_t OrganismComponent::getID() {
	return id++;
}
