#include "RigidBodyComponent.h"

#include "game.h"
#include "gameGUI.h"

void RigidBodyComponent::OnInit()
{
	transform = &entity->GetComponent<TransformComponent>();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(transform->position.x, transform->position.y);
	bodyDef.linearDamping = 0.5f;

	body = Game::Get()->getPhysics().CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(transform->width * transform->scale / 2, transform->height * transform->scale / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	fixture = body->CreateFixture(&fixtureDef);
}

void RigidBodyComponent::OnUpdate(float delta)
{
	transform->position.x = body->GetPosition().x;
	transform->position.y = body->GetPosition().y;
}

void RigidBodyComponent::OnDraw()
{
	if (Game::Get()->getGUI().debugMode)
	{
		GPU_Rectangle(Game::Get()->getWindow().GetTarget(),
			body->GetPosition().x - transform->width * transform->scale / 2,
			body->GetPosition().y - transform->height * transform->scale / 2,
			body->GetPosition().x + transform->width * transform->scale / 2,
			body->GetPosition().y + transform->height * transform->scale / 2,
			SDL_Color{ 255, 255, 255, 255 });
	}
}

void RigidBodyComponent::ApplyLinearImpulse(const Vector2D& impulse)
{
	if (!body)
	{
		LOG_ERROR("Can't apply impulse on a unintialized body");
		return;
	}

	body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
}

void RigidBodyComponent::ApplyLinearForce(const Vector2D& force)
{
	if (!body)
	{
		LOG_ERROR("Can't apply force on a unintialized body");
		return;
	}

	body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void RigidBodyComponent::OnClear()
{
}
