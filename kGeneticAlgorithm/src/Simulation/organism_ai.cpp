#include "organism_ai.h"
#include "organism.h"

OrganismAI::OrganismAI() {}

OrganismAI::~OrganismAI() {}

void OrganismAI::OnInit()
{
	aiState = AI_STATE::NEUTRAL;

	boredomMax = std::rand() % 200 + 50;
	tirednessMax = std::rand() % 200 + 50;
	direction = std::rand() % 3 + 1;
}

void OrganismAI::OnUpdate()
{
	switch (aiState) {
	case NEUTRAL:
	{
		break;
	}
	case FLEEING:
	{

		break;
	}
	case PREDATING:
	{

		break;
	}
	case SCAVENGING:
	{

		break;
	}
	default:

		break;
	};
}
