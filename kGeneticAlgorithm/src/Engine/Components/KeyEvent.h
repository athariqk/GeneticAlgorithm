#pragma once

#include "game.h"
#include "Components.h"

class Game;

class KeyEvent : public Component {
public:
    KeyEvent() {}
    ~KeyEvent() {}

    void OnUpdate() override
    {
        if (Game::Get()->m_event.type == SDL_KEYDOWN) {
            switch (Game::Get()->m_event.key.keysym.sym) {
            case SDLK_w:
				Game::camera.y = -6;
                break;
            case SDLK_a:
				Game::camera.x = -6;
                break;
            case SDLK_d:
				Game::camera.x = 6;
                break;
            case SDLK_s:
				Game::camera.y = 6;
                break;
			default:
				break;
            }
        }

		if (Game::Get()->m_event.type == SDL_KEYUP) {
			switch (Game::Get()->m_event.key.keysym.sym) {
			case SDLK_w:
				Game::camera.y = 0;
				break;
			case SDLK_a:
				Game::camera.x = 0;
				break;
			case SDLK_d:
				Game::camera.x = 0;
				break;
			case SDLK_s:
				Game::camera.y = 0;
				break;
			}
		}
    }
};
