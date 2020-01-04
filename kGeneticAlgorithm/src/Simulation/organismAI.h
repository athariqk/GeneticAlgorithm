#pragma once
#include "Entities/EntitySystem.h"
#include "Vector2D.h"

#include "nutrient.h"

/**
 * Simple predefined AI for the organisms
 * neural network could be used later instead
*/

enum BehaviourState {
	Idling = 0,
	RunAndTumble = 1,
	Absorbing = 2
};

class OrganismAI : public Component {
public:
	OrganismAI(float organismSpeed, float aiInterval, int hunger) :
		moveSpeed(organismSpeed), actInterval(aiInterval), maxHunger(hunger) {}
	~OrganismAI() {}

	void OnInit() override;
	void OnUpdate() override;

	void runAndTumble();
	void absorbNutrient();

	Vector2D& getRandomDirection();

	float moveSpeed;

	int maxHunger;
	int hunger;

	bool runAI = false;

private:
	BehaviourState behaviourState;
	TransformComponent* transform;
	ColliderComponent* collider;

	float actInterval = 10;
	float movingInterval = 10;
	float actTimer = 0;

	bool isNutrientFound = false;
	bool hasMoved = false;
};
