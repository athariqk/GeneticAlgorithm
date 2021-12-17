#pragma once
#include "config.h"

#include "Components/Components.h"

#include <random>

class Nutrient : public Component {
public:
	Nutrient(int energy) : curEnergy(energy) {}
	~Nutrient() {}

	float curEnergy;

	void OnInit() override;
	void OnUpdate(float delta) override;

	//! \todo Implement proper ID counting
	size_t getID() const { return id; }

	bool caught = false;
	Vector2D organismPos;

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	RigidBodyComponent* rb;

	size_t id = 0;
};
