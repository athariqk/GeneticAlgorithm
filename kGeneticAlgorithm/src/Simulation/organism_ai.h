#pragma once

#include "Entities/Components.h"

class OrganismAI : public Component
{
public:
	OrganismAI();
	~OrganismAI();

	enum AI_STATE {
		NEUTRAL,
		FLEEING,
		PREDATING,
		SCAVENGING
	};

	void OnInit() override;

	void OnUpdate() override;

	float boredom;
	float tiredness;

	int boredomMax;
	int tirednessMax;

	int direction;

private:
	AI_STATE aiState;
};
