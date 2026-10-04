#pragma once

class Font;

namespace Fonts
{
    enum class FontType
    {
        Default,
        TwoWeekendGoSemibold,
        TwoWeekendGoRegular,
        GoodOldDos
    };

    void Initialize();
    Font& GetFont(FontType fontType);
}