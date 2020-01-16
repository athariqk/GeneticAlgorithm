#pragma once
#include "Components/Components.h"

#include "ImGui/ImGuiLayer.h"

class GameGUI {
public:
    GameGUI() {}
    ~GameGUI() = default;

    void OnInit();
    void OnImGuiRender();
    void OnImGuiEvent();
    void OnImGuiClear();

	bool debugMode = false;

private:
    ImGuiLayer* imgui;
	bool showCreateSpecies = false;

	std::string sGenus;
	std::string sEpithet;
};
