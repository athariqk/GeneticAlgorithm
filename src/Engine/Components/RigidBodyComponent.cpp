#include "RigidBodyComponent.h"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include "Camera.h"
#include "box2d/box2d.h"
#include "Physics/Physics2D.h"

#include "scene.h"
#include "gui.h"
#include "TransformComponent.h"

#include "Logger.h"

void RigidBodyComponent::OnInit()
{
	transform = &entity->GetComponent<TransformComponent>();

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(transform->position.x, transform->position.y);
	bodyDef.linearDamping = 0.5f;

	bodyId = Scene::Get()->GetPhysics().CreateBody(&bodyDef);

    b2Polygon dynamicBox = b2MakeBox(
        transform->width * transform->scale / 2,
        transform->height * transform->scale / 2);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;

    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void RigidBodyComponent::OnUpdate(float delta)
{
    auto [x, y] = b2Body_GetPosition(bodyId);
	transform->position.x = x;
	transform->position.y = y;
}

void RigidBodyComponent::OnDraw()
{
	if (Scene::Get()->GetGUI().debugMode)
	{
        SDL_Renderer* renderer = Scene::Get()->GetWindow().GetRenderer();

		auto [x, y] = transform->GetScreenPosition();
        const SDL_FRect rect = {
            x - transform->width * 0.5f * transform->scale,
            y - transform->height * 0.5f * transform->scale,
            transform->width * transform->scale,
            transform->height * transform->scale
        };

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &rect);
	}
}

void RigidBodyComponent::ApplyLinearImpulse(const Vector2D& impulse)
{
	if (!b2Body_IsValid(bodyId))
	{
		LOG_ERROR("Can't apply impulse on a uninitialized body");
		return;
	}

    b2Body_ApplyLinearImpulseToCenter(bodyId, b2Vec2(impulse.x, impulse.y), true);
}

void RigidBodyComponent::ApplyLinearForce(const Vector2D& force)
{
	if (!b2Body_IsValid(bodyId))
	{
		LOG_ERROR("Can't apply force on a uninitialized body");
		return;
	}

    b2Body_ApplyForceToCenter(bodyId, b2Vec2(force.x, force.y), true);
}

void RigidBodyComponent::OnClear()
{
}
