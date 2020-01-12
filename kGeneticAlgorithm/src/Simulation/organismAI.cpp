#include "organismAI.h"
#include "organism.h"
#include "game.h"

#include "Simulation/environment.h"

#include "Collision.h"

#include <random>
#include <ctime>

void OrganismAI::OnInit() {
	behaviourState = BehaviourState::Idling;

	/* Get all of the neccesary components */
	transform = &entity->GetComponent<TransformComponent>();
	collider = &entity->GetComponent<ColliderComponent>();
	organism = &entity->GetComponent<OrganismComponent>();

	if (transform == NULL) {
		LOG_ERROR("Agent has no transform component!");
		runAI = false;
	} else{
		transform->speed = moveSpeed;
		runAI = true;
	}
}

void OrganismAI::OnUpdate() {
	if (runAI) {
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

			/* Absorb the nutrient if energy is below
			half of the organism's energy capacity */
			if (isNutrientFound && organism->curEnergy <
				organism->genome->m_DNA.energyCapacity / 2)
			{
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
				caughtNutrient->caught = false;
				actTimer = 0;
			}

			if (actTimer > actInterval * 5) {
				behaviourState = BehaviourState::RunAndTumble;
				isNutrientFound = false;
				caughtNutrient->caught = false;
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
	std::uniform_int_distribution<> dis(
		-2,
		2);

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
	auto& nutrients(Game::Get()->getEntityManager().GetGroup(Game::groupLabels::NutrientsGroup));

	for (auto& e : nutrients) {
		if (Collision::AABB(collider->collider, e->GetComponent<ColliderComponent>().collider))
		{
			caughtNutrient = &e->GetComponent<Nutrient>();
			actTimer = 0;
			isNutrientFound = true;
			LOG_TRACE("Organism {} Collider hit nutrient {}",
				entity->GetComponent<OrganismComponent>().getID(),
				caughtNutrient->getID()
			);
		}
	}
}

void OrganismAI::absorbNutrient() {
	if (caughtNutrient == nullptr) {
		LOG_ERROR("Nutrient is not found while trying to absorb it!");
		isNutrientFound = false;
	}
	else {
		transform->velocity.Zero();

		caughtNutrient->caught = true;
		caughtNutrient->organismPos = transform->position;

		if (organism->curEnergy < organism->genome->m_DNA.energyCapacity) {
			if (caughtNutrient->curEnergy > 0)
				organism->curEnergy += absorbSpeed;

			caughtNutrient->curEnergy -= absorbSpeed;

			/* Increase the fitness while absorbing nutrients */
			organism->fitness += 0.05f;
		}
	}
}

std::string OrganismAI::getCurrentBehaviour() {
	std::string result;

	if (behaviourState == BehaviourState::Idling) {
		/* This is because the idle state currently
		just only changes the direction */
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
