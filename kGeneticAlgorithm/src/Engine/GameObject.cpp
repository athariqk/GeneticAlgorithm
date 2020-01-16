#include "game.h"

#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objtexture = TextureManager::LoadTexture(texturesheet);

	xPos = x;
	yPos = y;
}

GameObject::~GameObject()
{}

void GameObject::Update() {
	xPos++;
	yPos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
    GPU_Blit(objtexture, &srcRect, Game::Get()->getWindow().GetTarget(), destRect.x, destRect.y);
}
