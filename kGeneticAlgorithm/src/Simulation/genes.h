#pragma once

#include <SDL.h>

#include <random>
#include <stdint.h>

class Genes {
public:
	Genes() {
		m_DNA.energyCapacity = getRandomValue(10, 100);
		m_DNA.speed = getRandomValue(1, 3);
		m_DNA.membraneColour = {
			(Uint8)getRandomValue(1, 255),
			(Uint8)getRandomValue(1,255),
			(Uint8)getRandomValue(1,255),
			150
		};
	}

	// Traits of the organism
	struct DNA {
		float energyCapacity;
		float speed;
		SDL_Color membraneColour;
	};

	DNA m_DNA;

	float getRandomValue(int min, int max) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(min, max);

		return dis(gen);
	}

	void crossover() {

	}

	void mutate() {

	}
};
