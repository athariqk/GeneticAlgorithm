#include "organismAI.h"
#include "organism.h"
#include "genes.h"
#include "game.h"

#include "Simulation/environment.h"

#include <random>
#include <ctime>

void OrganismAI::OnInit() {
	behaviourState = BehaviourState::Idling;

	/* Get all of the neccesary components */
	transform = &entity->GetComponent<TransformComponent>();
	organism = &entity->GetComponent<OrganismComponent>();
	rb = &entity->GetComponent<RigidBodyComponent>();

	if (transform == NULL) {
		LOG_ERROR("Agent has no transform component!");
		runAI = false;
	} else{
		runAI = true;
	}
}

void OrganismAI::OnUpdate(float delta) {
	if (runAI) {
		if (organism->curEnergy > organism->
			genome.energyCapacity / 2)
		{
			reproduceInterval += 0.1f /* Reproduction rate */;
		}

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
				organism->genome.energyCapacity / 2)
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
				isAbsorbing = false;
				caughtNutrient->caught = false;
				actTimer = 0;
				behaviourState = BehaviourState::RunAndTumble;
			}

			if (actTimer > actInterval * 5) {
				isNutrientFound = false;
				caughtNutrient->caught = false;
				isAbsorbing = false;
				actTimer = 0;
				behaviourState = BehaviourState::Evaluate;
			}
			break;

		case BehaviourState::Evaluate:
			actTimer++;

			if (organism->curEnergy > organism->genome.
				energyCapacity / 2 && reproduceInterval > 100)
			{
				if (reproduced)
					reproduced = false;

				reproduce(&organism->genome);
			}
			else {
				actTimer = 0;
				behaviourState = BehaviourState::RunAndTumble;
			}

			if (actTimer > actInterval * 2)
			{
				actTimer = 0;
				behaviourState = BehaviourState::RunAndTumble;
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
		-1,
		1);

	direction.x = dis(gen);
	direction.y = dis(gen);

	return direction;
}

void OrganismAI::runAndTumble() {
	if(!hasMoved) {
		hasMoved = true;
		rb->ApplyLinearImpulse(getRandomDirection() * moveSpeed * 100000);
	}
}

void OrganismAI::checkForNutrients() {
	auto& nutrients(Game::Get()->getEntityManager().GetGroup(Game::groupLabels::NutrientsGroup));
}

void OrganismAI::absorbNutrient() {
	if (caughtNutrient == nullptr) {
		LOG_ERROR("Nutrient is not found while trying to absorb it!");
		isNutrientFound = false;
	}
	else {
		caughtNutrient->caught = true;
		caughtNutrient->organismPos = transform->position;

		if (organism->curEnergy < organism->genome.energyCapacity) {
			if (caughtNutrient->curEnergy > 0)
				organism->curEnergy += absorbSpeed;

			caughtNutrient->curEnergy -= absorbSpeed;

			/* Increase the fitness while absorbing nutrients */
			organism->fitness += 0.05f;
		}
	}
}

void OrganismAI::reproduce(Genes* genes) {
	if (!reproduced) {
		reproduced = true;
		reproduceInterval = 0;
		organism->species->addOrganism(*genes, true);

		/* Set X position to the parent */
		organism->species->organisms.back()->
			entity->GetComponent<TransformComponent>().
			position.x = transform->position.x;

		/* Set y position to the parent */
		organism->species->organisms.back()->
			entity->GetComponent<TransformComponent>().
			position.y = transform->position.y;

		organism->curEnergy -= 10;

		LOG_INFO("Organism {} reproduced", organism->getID());
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
	if (behaviourState == BehaviourState::Evaluate) {
		result = "Evaluating";
	}

	return result;
}
