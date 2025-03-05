#include "nutrient.h"

#include "Camera.h"
#include "Random.h"
#include "scene.h"

#include "Components/RigidBodyComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

void Nutrient::OnInit() {
    id = Random::RandomInt(5, 10);
    int size = Random::RandomInt(10, 20);

    const auto &camera = Scene::GetCamera();
    float spawnX = camera.position.x + Random::RandomFloat(-100, 100);
    float spawnY = camera.position.y + Random::RandomFloat(-100, 100);

    transform = &entity->AddComponent<TransformComponent>(spawnX, spawnY, size, size);

    sprite = &entity->AddComponent<SpriteComponent>("assets/nutrient.png");
    rb = &entity->AddComponent<RigidBodyComponent>();
}

void Nutrient::OnUpdate(float delta) {
    if (curEnergy < 0)
        entity->Destroy();
}
