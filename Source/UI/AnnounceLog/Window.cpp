#include "Window.hpp"
#include <raylib.h>
#include "../Scale.hpp"
#include <print>

namespace
{
    int padding = 10;
    int kBaseTextSize = 30;
}

void UI::AnnounceLog::Render(Replay::State &state)
{
    const float scale = UI::GetScale();
    int height = 50;
    int posX = UI::sizes.ToolboxWidth;
    int posY = UI::positions.ControlPanelY - (UI::sizes.ControlPanelHeight / 2);

    auto textSize = state.Log.Draw(0, 0, kBaseTextSize * scale, true);
    DrawRectangle(posX + padding, posY - padding - textSize.y + (kBaseTextSize * scale), textSize.x, textSize.y, Color(58, 58, 58, 128));
    state.Log.Draw(posX + padding + 5, posY - padding - textSize.y + (kBaseTextSize * scale), kBaseTextSize * scale);
}