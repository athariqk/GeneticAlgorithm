#include "organismAI.h"
#include "organism.h"
#include "game.h"

#include "Simulation/environment.h"

#include "Collision.h"

#include <random>
#include <ctime>

void OrganismAI::OnInit() {
	behaviourState = BehaviourState::Idling;

	// Get all neccesary components
	transform = &entity->GetComponent<TransformComponent>();
	collider = &entity->GetComponent<ColliderComponent>();

	if (transform == NULL) {
		LOG_ERROR("Agent has no transform component!");
		runAI = false;
	} else{
		transform->speed = moveSpeed;
		runAI = true;
	}

	organismEnergy = entity->GetComponent<OrganismComponent>().energy;
}

void OrganismAI::OnUpdate() {
	if (runAI) {
		entity->GetComponent<OrganismComponent>().energy = organismEnergy;

		if(!isAbsorbing)
			organismEnergy -= 0.01f;

		if (organismEnergy < 0)
			organismEnergy = 0;

		if (organismEnergy > 100)
			organismEnergy = 100;

		switch (behaviourState) {
		case BehaviourState::Idling:
			hasMoved = false;
			actTimer++;
			
			if (actTimer > 0.01f) {
				behaviourState = BehaviourState::RunAndTumble;
				actTimer = 0;
			}
			break;

		case BehaviourState::RunAndTumble:
			actTimer++;
			runAndTumble();
			checkForNutrients();

			if (isNutrientFound && caughtNutrient->energy > 0) {
				behaviourState = BehaviourState::Absorbing;
				actTimer = 0;
			}

			if (actTimer > actInterval) {
				behaviourState = BehaviourState::Idling;
				actTimer = 0;
			}
			break;

		case BehaviourState::Absorbing:
			isAbsorbing = true;
			absorbNutrient();
			actTimer++;

			if (!isNutrientFound) {
				behaviourState = BehaviourState::RunAndTumble;
				isAbsorbing = false;
				actTimer = 0;
			}

			if (actTimer > actInterval) {
				behaviourState = BehaviourState::RunAndTumble;
				isNutrientFound = false;
				isAbsorbing = false;
				actTimer = 0;
			}
			break;

		default:
			break;
		}
	}
}

Vector2D& OrganismAI::getRandomDirection() {
	Vector2D direction;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(-5, 5);

	direction.x = dis(gen);
	direction.y = dis(gen);

	return direction;
}

void OrganismAI::runAndTumble() {
	if(!hasMoved) {
		hasMoved = true;
		transform->velocity = getRandomDirection();
	}
}

void OrganismAI::checkForNutrients() {
	auto& nutrients(Game::Get()->getEntityManager().
		GetGroup(Game::groupLabels::NutrientsGroup));

	for (auto e : nutrients) {
		if (Collision::AABB(collider->collider,
			e->GetComponent<ColliderComponent>().collider))
		{
			caughtNutrient = &e->GetComponent<Nutrient>();
			actTimer = 0;
			isNutrientFound = true;
		}
	}
}

void OrganismAI::absorbNutrient() {
	if (caughtNutrient == nullptr) {
		LOG_ERROR("Nutrient is not found while trying to absorb it!");
		isNutrientFound = false;
	}
	else if (caughtNutrient->energy == 0) {
		isNutrientFound = false;
		if (caughtNutrient != nullptr) {
			caughtNutrient = nullptr;
		}
	}
	else {
		transform->velocity.Zero();

		///! \todo The energy exchange should be
		//! evenly distributed
		organismEnergy += caughtNutrient->energy * absorbSpeed;
		caughtNutrient->energy -= absorbSpeed;

		if (caughtNutrient->energy == 0) {
			isNutrientFound = false;

			if (caughtNutrient != nullptr) {
				caughtNutrient = nullptr;
			}
		}
	}
}

std::string OrganismAI::getCurrentBehaviour() {
	std::string result;

	if (behaviourState == BehaviourState::Idling) {
		// This is because the idle state currently
		// just only changes the direction
		result = "Run & Tumble";
	}
	if (behaviourState == BehaviourState::RunAndTumble) {
		result = "Run & Tumble";
	}
	if (behaviourState == BehaviourState::Absorbing) {
		result = "Absorbing nutrient";
	}

	return result;
}
