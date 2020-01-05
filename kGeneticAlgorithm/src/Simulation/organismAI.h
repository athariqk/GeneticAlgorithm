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
	OrganismAI(float organismSpeed, float aiInterval) :
		moveSpeed(organismSpeed), actInterval(aiInterval) {}
	~OrganismAI() {}

	void OnInit() override;
	void OnUpdate() override;

	void runAndTumble();
	void absorbNutrient();
	void checkForNutrients();

	Vector2D& getRandomDirection();

	std::string getCurrentBehaviour();

	float moveSpeed;
	float absorbSpeed = 0.1f;

	bool runAI = false;

private:
	BehaviourState behaviourState;
	TransformComponent* transform;
	ColliderComponent* collider;
	Nutrient* caughtNutrient;

	float actInterval = 10;
	float movingInterval = 10;
	float actTimer = 0;

	float organismEnergy;

	bool isNutrientFound = false;
	bool hasMoved = false;
	bool isAbsorbing = false;
};
