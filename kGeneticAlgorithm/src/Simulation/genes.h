#pragma once

#include <random>
#include <stdint.h>

class Genes {
public:
	Genes() {
		m_DNA = {
			getRandomValue(10, 100),
			getRandomValue(10, 100),
			getRandomValue(5, 20),
			getRandomValue(5, 50),
			getRandomValue(5, 50),
			getRandomValue(1, 5)
		};
	}

	// Traits of the organism
	struct DNA {
		float aggression, fear, size,
			speed, strength, mutationRate;
	};

	DNA m_DNA;

	float getRandomValue(int min, int max) {
		return static_cast<float>(std::rand() % max + min);
	}

	void crossover() {

	}

	void mutate() {

	}
};