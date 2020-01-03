#pragma once
#include "Entities/Components.h"

#include "ImGui/ImGuiLayer.h"

class GameGUI {
public:
    GameGUI() {}
    ~GameGUI() = default;

    void OnInit();
    void OnImGuiRender();
    void OnImGuiEvent();
    void OnImGuiClear();

private:
    ImGuiLayer* imgui;
    bool show_demo_window = true;
};
