#include "microbe_ai.h"
#include "microbe.h"

MicrobeAI::MicrobeAI() {}

MicrobeAI::~MicrobeAI() {}

void MicrobeAI::OnInit()
{
	aiState = AI_STATE::NEUTRAL;

	boredomMax = std::rand() % 200 + 50;
	tirednessMax = std::rand() % 200 + 50;
	direction = std::rand() % 3 + 1;
}

void MicrobeAI::OnUpdate()
{
	switch (aiState) {
	case NEUTRAL:
	{
		boredom++;
		if (boredom > boredomMax) {
			aiState = AI_STATE::SCAVENGING;
			tiredness += 1.0f;
		}
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
		if(direction == 1)
			entity->GetComponent<TransformComponent>().position.x += 5.0f;
		if(direction == 2)
			entity->GetComponent<TransformComponent>().position.x -= 5.0f;
		if(direction == 3)
			entity->GetComponent<TransformComponent>().position.y += 5.0f;

		if (tiredness > tirednessMax) {
			aiState = AI_STATE::NEUTRAL;
			boredom += 1.0f;
		}

		break;
	}
	default:

		break;
	};
}
