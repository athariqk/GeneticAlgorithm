#include "organismAI.h"
#include "organism.h"
#include "game.h"

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

	LOG_INFO("Initialized AI for organism {}",
		entity->GetComponent<OrganismComponent>().getID());
}

void OrganismAI::OnUpdate() {
	if (runAI) {
		hunger++;

		switch (behaviourState) {
		case BehaviourState::Idling:
			transform->velocity.Zero();
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

			if (isNutrientFound) {
				behaviourState = BehaviourState::Absorbing;
				actTimer = 0;
			}

			if (actTimer > actInterval) {
				behaviourState = BehaviourState::Idling;
				actTimer = 0;
			}
			break;

		case BehaviourState::Absorbing:
			transform->velocity.Zero();
			absorbNutrient();
			actTimer++;

			if (actTimer > actInterval) {
				behaviourState = BehaviourState::RunAndTumble;
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

void OrganismAI::absorbNutrient() {

}
