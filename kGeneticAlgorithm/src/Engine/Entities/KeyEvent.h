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
                LOG_INFO("Pressed W key!");
                break;
            case SDLK_a:
                LOG_INFO("Pressed A key!");
                break;
            case SDLK_d:
                LOG_INFO("Pressed D key!");
                break;
            case SDLK_s:
                LOG_INFO("Pressed S key!");
                break;
            }
        }
    }
};