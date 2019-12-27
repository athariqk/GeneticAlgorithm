#pragma once

#include "Entities/Components.h"

class MicrobeAI : public Component
{
public:
	MicrobeAI();
	~MicrobeAI();

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
