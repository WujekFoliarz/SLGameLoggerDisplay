#include "DroppedItem.hpp"
#include "../ItemNameFormatter.hpp"

ConditionChecker::ConditionCheckResult EventConditions::DroppedItem::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        result.AnnounceLogMessage = std::format(
            "Player [{}] {} dropped {}",
            Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
            point.GiverNickname,
            ItemNameFormatter::GetFormattedItemName(point.CustomData));
    }

    return result;
}
