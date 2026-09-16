#include "Scale.hpp"
#include "imgui.h"
#include <algorithm>

namespace
{
    constexpr float REFERENCE_WIDTH  = 1920.0f;
    constexpr float REFERENCE_HEIGHT = 1080.0f;
    constexpr float BASE_SCALE_MULTIPLIER = 1.5f;

    ImGuiStyle baseStyle;
    float lastScale = -1.0f;
    bool initialized = false;
}

float UI::GetScale()
{
    ImVec2 display = ImGui::GetIO().DisplaySize;
    float scaleX = display.x / REFERENCE_WIDTH;
    float scaleY = display.y / REFERENCE_HEIGHT;
    return std::min(scaleX, scaleY);
}

void UI::InitScale()
{
    baseStyle = ImGui::GetStyle(); 
    initialized = true;
    lastScale = -1.0f;           
}

void UI::ApplyScale()
{
    if (!initialized)
    {
        InitScale();
    }

    float scale = GetScale();
    if (scale == lastScale)
    {
        return;
    }

    ImGuiStyle &style = ImGui::GetStyle();
    style = baseStyle;         
    style.ScaleAllSizes(scale); 
    ImGui::GetIO().FontGlobalScale = scale * BASE_SCALE_MULTIPLIER;

    lastScale = scale;
}