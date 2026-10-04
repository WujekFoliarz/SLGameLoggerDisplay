#include "Window.hpp"
#include <raylib.h>
#include "../Scale.hpp"
#include <print>

namespace
{
    int padding = 10;
    int kBaseTextSize = 30;
}

void SLUI::AnnounceLog::Render(Replay::State &state)
{
    const float scale = SLUI::GetScale();
    int height = 50;
    int posX = SLUI::sizes.ToolboxWidth;
    int posY = SLUI::positions.ControlPanelY - (SLUI::sizes.ControlPanelHeight / 2);

    const int textPosX = posX + padding + 5;
    auto textSize = state.Log.Draw(textPosX, 0, kBaseTextSize * scale, true);
    DrawRectangle(posX + padding, posY - padding - textSize.y + (kBaseTextSize * scale), textSize.x + 5, textSize.y, Color(0, 0, 170, 128));
    state.Log.Draw(textPosX, posY - padding - textSize.y + (kBaseTextSize * scale), kBaseTextSize * scale);
}