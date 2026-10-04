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

    auto textSize = state.Log.Draw(0, 0, kBaseTextSize * scale, true);
    DrawRectangle(posX + padding, posY - padding - textSize.y + (kBaseTextSize * scale), textSize.x, textSize.y, Color(58, 58, 58, 128));
    state.Log.Draw(posX + padding + 5, posY - padding - textSize.y + (kBaseTextSize * scale), kBaseTextSize * scale);
}