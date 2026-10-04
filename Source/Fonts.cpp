#include "Fonts.hpp"
#include <raylib.h>
#include <unordered_map>
#include <vector>

namespace
{
    bool Initialized = false;
    std::unordered_map<Fonts::FontType, Font> FontMap;
}

void Fonts::Initialize()
{
    if (Initialized)
        return;
    FontMap.emplace(FontType::TwoWeekendGoSemibold, LoadFontEx(RESOURCE_PATH "Fonts/twoweekendgo-semibold.otf", 96, 0, 0));
    FontMap.emplace(FontType::TwoWeekendGoRegular, LoadFontEx(RESOURCE_PATH "Fonts/twoweekendgo-regular.otf", 96, 0, 0));

    std::vector<int> latinCodepoints;
    for (int codepoint = 0x20; codepoint <= 0x7E; ++codepoint)
        latinCodepoints.push_back(codepoint);
    for (int codepoint = 0xA0; codepoint <= 0x024F; ++codepoint)
        latinCodepoints.push_back(codepoint);

    FontMap.emplace(FontType::GoodOldDos, LoadFontEx(RESOURCE_PATH "Fonts/Good-Old-Dos.ttf", 96, latinCodepoints.data(), static_cast<int>(latinCodepoints.size())));
    Initialized = true;
}

Font &Fonts::GetFont(FontType fontType)
{
    return FontMap.at(fontType);
}
