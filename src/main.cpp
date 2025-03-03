#include "config.h"
#include "scene.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>

#include "Logger.h"

int main(int argc, char *argv[]) {
    Logger::Init();
    LOG_TRACE("Log initialized");

    constexpr char title[20] = "kGeneticAlgorithm";
    auto *window = new Window(title, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    // Report info
    LOG_INFO("SDL Renderer name: {}", SDL_GetRendererName(window->GetRenderer()));
    LOG_TRACE("----- End of system information -----");

    auto *scene = new Scene(*window);
    scene->Init();

    constexpr int fps = 60;
    constexpr int frameDelay = 1000 / fps;
    double delta = 0;

    Uint32 lastFPSUpdateTime = 0;
    int frameCount = 0;
    float currentFPS = 0.0f;

    uint64_t ticks = 0;

    while (Scene::Get()->running()) {
        const uint32_t frameStart = SDL_GetTicks();

        scene->HandleEvents();
        scene->Update(delta, ticks);
        scene->Render();

        const uint32_t currentTime = SDL_GetTicks();
        delta = static_cast<double>(currentTime - frameStart) / 1000.0;

        if (currentTime - lastFPSUpdateTime > 1000) {
            // Update FPS once per second
            currentFPS = frameCount * 1000.0f / (currentTime - lastFPSUpdateTime);
            frameCount = 0;
            lastFPSUpdateTime = currentTime;

            char titleWAttrs[100];
            sprintf(titleWAttrs, "%s - FPS: %.1f - Delta: %.5f", title, currentFPS, delta);
            window->SetTitle(titleWAttrs);
        }

        if (frameDelay > delta) {
            SDL_Delay(frameDelay - delta);
        }

        frameCount++;
        ticks++;
    }

    delete (window);
    Scene::Clean();
    delete (scene);

    return 0;
}
