#include "nutrient.h"

void Nutrient::OnInit()
{
	id = std::rand() % 20 + 5;
	transform = &entity->AddComponent<TransformComponent>
		(std::rand() % WINDOW_WIDTH + 10, std::rand() % WINDOW_HEIGHT + 10, 10, 10);
	sprite = &entity->AddComponent<SpriteComponent>("assets/nutrient.png");
	rb = &entity->AddComponent<RigidBodyComponent>();
}

void Nutrient::OnUpdate(float delta)
{
	if (curEnergy < 0)
		entity->Destroy();
}
