#include "nutrient.h"

#include "config.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/RigidBodyComponent.h"

void Nutrient::OnInit()
{
	id = std::rand() % 20 + 5;
	int size = std::rand() % 10 + 20;
	transform = &entity->AddComponent<TransformComponent>
		(std::rand() % WINDOW_WIDTH + 10,
         std::rand() % WINDOW_HEIGHT + 10,
         size,
         size);
	sprite = &entity->AddComponent<SpriteComponent>("assets/nutrient.png");
	rb = &entity->AddComponent<RigidBodyComponent>();
}

void Nutrient::OnUpdate(float delta)
{
	if (curEnergy < 0)
		entity->Destroy();
}
