#pragma once

#include <SDL.h>

#include <random>
#include <stdint.h>

class Genes {
public:
	Genes() {
		energyCapacity = getRandomValue(10, 100);
		speed = getRandomValue(1, 3);
		size = getRandomValue(5, 10);
		membraneColour = {
			(Uint8)getRandomValue(1, 255),
			(Uint8)getRandomValue(1,255),
			(Uint8)getRandomValue(1,255),
			150
		};
		aggresiveness = getRandomValue(1, 20);
	}

	// Traits (Parameters) of the organisms
	float energyCapacity;
	float speed;
	float size;
	float aggresiveness;
	SDL_Color membraneColour;

	float getRandomValue(int min, int max) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(min, max);

		return dis(gen);
	}

	bool mutate(uint32_t mutationProb, float mutationRate) {
		//! \todo Fix mutation probability calculations
		if ((uint32_t)getRandomValue(0, mutationProb * 2) < mutationProb) {
			energyCapacity += getRandomValue(-mutationRate, mutationRate);
			speed += getRandomValue(-mutationRate, mutationRate);
			size += getRandomValue(-mutationRate, mutationRate);
			aggresiveness += getRandomValue(-mutationRate, mutationRate);
			return  true;
		}

		return false;
	}
};
