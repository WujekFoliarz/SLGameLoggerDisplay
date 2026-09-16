#pragma once

namespace UI
{
    struct Sizes
    {
        float ToolboxWidth = 0.0f;
        float ControlPanelHeight = 0.0f;
    };

    struct Positions
    {
        float ControlPanelY = 0.0f;
    };

    float GetScale();
    void InitScale();
    void ApplyScale();
    inline Sizes sizes{};
    inline Positions positions{};
}