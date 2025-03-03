#pragma once

#include "Components/EntitySystem.h"
#include "Window.h"

class Environment;
class GUI;
class Physics2D;
class AudioManager;
class Camera;
union SDL_Event;

class Scene {
public:
    explicit Scene(Window &m_mainWindow);

    ~Scene();

    void Init();

    void HandleEvents();

    void Update(double p_delta, uint64_t p_ticks);

    void Render() const;

    static void Clean();

    bool running() const { return m_running; }

    static Scene *Get();

    Window &GetWindow() const;

    static EntityManager &GetEntityManager();

    static Environment &GetEnvironment();

    static GUI &GetGUI();

    static Physics2D &GetPhysics();

    static AudioManager &GetAudio();

    static Camera &GetCamera();

    uint64_t &GetTick() { return ticks; }

    void MoveCamera(float x, float y);

    static SDL_Event m_event;

    enum groupLabels : std::size_t { NutrientsGroup, SpeciesGroup, OrganismsGroup, Other };

private:
    bool m_running = false;

    static Scene *staticInstance;

    Window &mainWindow;

    uint64_t ticks = 0;

    void HandleCameraMovement(double p_delta) const;

    const float cameraSpeed = 0.5f;

    bool isPanning = false;
};
