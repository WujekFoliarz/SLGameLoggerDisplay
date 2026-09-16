#include "Window.hpp"
#include <imgui.h>
#include <raylib.h>
#include <algorithm>

#include "../Scale.hpp"
#include "../../Utils.hpp"

namespace
{
    constexpr float BASE_HEIGHT = 80.0f;

    bool paused = false;
}

void UI::ControlPanel::Render(Replay::State &state)
{
    const float scale = UI::GetScale();

    const float positionX = UI::sizes.ToolboxWidth;
    const float width = GetScreenWidth() - positionX;
    const float height = BASE_HEIGHT * scale;
    const float positionY = GetScreenHeight() - height;
    UI::sizes.ControlPanelHeight = height;
    UI::positions.ControlPanelY = positionY;

    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);

    ImGui::SetNextWindowPos(ImVec2(positionX, positionY), ImGuiCond_Always);

    ImGui::Begin("Control Panel", nullptr,
                 ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoTitleBar);

    float progress = 0.0f;

    if (state.TickCount > 0)
    {
        progress = static_cast<float>(state.CurrentTick) / static_cast<float>(state.TickCount);
    }

    ImGui::SetNextItemWidth(-1.0f);

    if (ImGui::SliderFloat("##Timeline", &progress, 0.0f, 1.0f, "", ImGuiSliderFlags_AlwaysClamp))
    {
        state.CurrentTick = static_cast<int>(
            progress * state.TickCount);
        state.Log.Clear();
        state.Points.clear();
    }

    if (ImGui::Button(paused ? "Play" : "Pause"))
    {
        paused = !paused;
    }
    state.Paused = paused;

    ImGui::SameLine();

    if (ImGui::Button("|<"))
    {
        state.CurrentTick = 0;
    }

    ImGui::SameLine();

    if (ImGui::Button("<"))
    {
        state.CurrentTick = (state.CurrentTick > 0) ? state.CurrentTick - 1 : 0;
    }

    ImGui::SameLine();

    if (ImGui::Button(">"))
    {
        state.CurrentTick = (state.CurrentTick < state.TickCount) ? state.CurrentTick + 1 : state.TickCount;
    }

    ImGui::SameLine();

    if (ImGui::Button(">|"))
    {
        state.CurrentTick = state.TickCount;
    }

    ImGui::SameLine();
    ImGui::Text("%.0f / %d", state.CurrentTick, state.TickCount);

    ImGui::SameLine();
    ImGui::Text(" | ");
    ImGui::SameLine();
    ImGui::Text("%s ", Utils::GetRoundTimeString(state.CurrentTick, state.TickRate).c_str());

    ImGui::SameLine();
    ImGui::SetNextItemWidth(150.0f);
    ImGui::DragFloat("Play speed", &state.PlaySpeed, 0.1f, -100.0f, 100.0f);
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        state.PlaySpeed = 1.0f;
    }

    ImGui::End();
}