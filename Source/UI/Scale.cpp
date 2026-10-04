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
    auto scaleBorder = [scale](float borderSize)
    {
        return borderSize > 0.0f ? std::max(borderSize * scale, 1.0f) : 0.0f;
    };
    style.WindowBorderSize = scaleBorder(baseStyle.WindowBorderSize);
    style.ChildBorderSize = scaleBorder(baseStyle.ChildBorderSize);
    style.PopupBorderSize = scaleBorder(baseStyle.PopupBorderSize);
    style.FrameBorderSize = scaleBorder(baseStyle.FrameBorderSize);
    style.TabBorderSize = scaleBorder(baseStyle.TabBorderSize);
    ImGui::GetIO().FontGlobalScale = scale * BASE_SCALE_MULTIPLIER;

    lastScale = scale;
}