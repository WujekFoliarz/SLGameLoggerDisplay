#include "UI.hpp"
#include "Style.hpp"
#include "Scale.hpp"
#include <rlImGui.h>

bool Initialized = false;

void UI::Initialize()
{
    if (Initialized) return;
    rlImGuiSetup(true);
    InitStyle();
    InitScale();
    Initialized = true;
}