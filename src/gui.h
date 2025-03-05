#pragma once

#include <string>

class ImGuiLayer;

class GUI {
public:
    GUI() {}
    ~GUI() = default;

    void OnInit();
    void OnImGuiRender();
    void OnImGuiEvent() const;
    void OnImGuiClear() const;

    bool debugMode = false;

private:
    ImGuiLayer *imgui{};
    bool showCreateSpecies = false;

    std::string sGenus;
    std::string sEpithet;

    float xRel, yRel;
};
