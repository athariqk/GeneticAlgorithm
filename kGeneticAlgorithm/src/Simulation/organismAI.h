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

class OrganismComponent;

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

	//! \brief Returns behaviour name
	std::string getCurrentBehaviour();

	float moveSpeed;
	float absorbSpeed = 0.2f;

	bool runAI = false;

private:
	BehaviourState behaviourState;
	OrganismComponent* organism;
	TransformComponent* transform;
	ColliderComponent* collider;
	Nutrient* caughtNutrient;

	float actInterval = 10;
	float movingInterval = 10;
	float actTimer = 0;

	bool isNutrientFound = false;
	bool hasMoved = false;
	bool isAbsorbing = false;
};
