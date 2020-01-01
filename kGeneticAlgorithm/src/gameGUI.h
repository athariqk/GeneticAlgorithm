#pragma once
#include "Entities/Components.h"

#include "ImGui/ImGuiLayer.h"

class GameGUI : public Component {
public:
    void OnInit() override;
    void OnEvent() override;
    void OnDraw() override;
	void OnClear() override;

private:
    ImGuiLayer* imgui;
    bool show_demo_window = true;
};