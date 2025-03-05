#pragma once

#include "scene.h"

#include "config.h"

#include <SDL3/SDL.h>

class PrimitiveShape {
public:
    /* \todo Add enum for color codes */
    static void DrawCircle(float posX, float posY, float radius, SDL_Color color, bool filled, bool edge) {
        SDL_Renderer *renderer = Scene::Get()->GetWindow().GetRenderer();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        if (filled) {
            // Approximate filled circle using many points
            for (int w = -radius; w <= radius; w++) {
                for (int h = -radius; h <= radius; h++) {
                    if (w * w + h * h <= radius * radius) {
                        SDL_RenderPoint(renderer, posX + w, posY + h);
                    }
                }
            }

            if (edge) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
                for (int i = 0; i < 360; i++) {
                    float angle = i * M_PI / 180.0f;
                    int x = posX + (radius + 2) * cos(angle);
                    int y = posY + (radius + 2) * sin(angle);
                    SDL_RenderPoint(renderer, x, y);
                }
            }
        } else {
            // Draw an outlined circle using the midpoint circle algorithm
            for (int i = 0; i < 360; i++) {
                float angle = i * M_PI / 180.0f;
                int x = posX + radius * cos(angle);
                int y = posY + radius * sin(angle);
                SDL_RenderPoint(renderer, x, y);
            }
        }
    }

    // Parameters doesn't work
    static void DrawRectangle(float posX, float posY, float size) {
        SDL_Renderer *renderer = Scene::Get()->GetWindow().GetRenderer();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_FRect rect = {posX, posY, size, size};
        SDL_RenderRect(renderer, &rect);
    }
};
