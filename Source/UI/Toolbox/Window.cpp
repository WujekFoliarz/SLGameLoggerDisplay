#include "Window.hpp"
#include "rlImGui.h"
#include "imgui.h"
#include "../Scale.hpp"
#include "Window.hpp"

#include <print>
#include "Window.hpp"
#include "Window.hpp"

namespace
{
    constexpr float BASE_WIDTH = 300.0f;
    float currentWidth = BASE_WIDTH;
}

void UI::Toolbox::Render(Replay::State &state)
{
    float scale = UI::GetScale();
    currentWidth = BASE_WIDTH * scale;
    UI::sizes.ToolboxWidth = currentWidth;
    ImGui::SetNextWindowSize(ImVec2(currentWidth, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

    ImGui::SetNextWindowSizeConstraints(
        ImVec2(0.0f, ImGui::GetIO().DisplaySize.y),
        ImVec2(FLT_MAX, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    static int highlightedPlayer = -1;
    ImGui::SeparatorText("Players:");
    for (auto &[id, playerData] : state.Players)
    {
        ImGui::TextColored(highlightedPlayer == id ? ImVec4(255, 255, 0, 255) : ImVec4(255, 255, 255, 255), "%d: %s", id, playerData.Nickname.c_str());
        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            highlightedPlayer = id;
        }
    }

    state.HighlightedPlayer = highlightedPlayer;
    currentWidth = ImGui::GetWindowWidth();

    ImGui::End();
}
