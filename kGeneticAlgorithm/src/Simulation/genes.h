#pragma once

#include <random>
#include <stdint.h>

class Genes {
public:
	Genes() {
		m_DNA = {
			getRandomValue(10, 100),
			getRandomValue(1, 3)
		};
	}

	// Traits of the organism
	struct DNA {
		float energyCapacity, speed;
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
