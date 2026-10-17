#pragma once
#include <string_view>

namespace ItemNameFormatter
{
    
    std::string_view GetFormattedItemName(std::string_view itemType);
    bool ShouldDisplayLogMessage(std::string_view itemType);
}