#include "Scale.hpp"
#include "imgui.h"
#include <algorithm>
#include <raylib.h>

namespace
{
    constexpr float REFERENCE_WIDTH  = 1920.0f;
    constexpr float REFERENCE_HEIGHT = 1080.0f;
    constexpr float BASE_SCALE_MULTIPLIER = 1.5f;

    ImGuiStyle baseStyle;
    float lastScale = -1.0f;
    bool initialized = false;
}

float SLUI::GetScale()
{
    float scaleX = GetScreenWidth() / REFERENCE_WIDTH;
    float scaleY = GetScreenHeight() / REFERENCE_HEIGHT;
    return std::min(scaleX, scaleY);
}

void SLUI::InitScale()
{
    baseStyle = ImGui::GetStyle(); 
    initialized = true;
    lastScale = -1.0f;           
}

void SLUI::ApplyScale()
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