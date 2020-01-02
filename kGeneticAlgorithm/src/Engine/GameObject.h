#pragma once

#include <SDL.h>

class GameObject {
public:
	GameObject(const char* texturesheet, int x, int y);

	~GameObject();

	void Render();
	void Update();

private:

	int xPos;
	int yPos;

	GPU_Image* objtexture;
	GPU_Rect srcRect, destRect;

};