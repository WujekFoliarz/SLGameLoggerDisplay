#include "PickingUpItem.hpp"
#include "../ItemNameFormatter.hpp"

ConditionChecker::ConditionCheckResult EventConditions::PickingUpItem::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (point.Handled)
        return result;

    if (!ItemNameFormatter::ShouldDisplayLogMessage(point.CustomData))
        return result;

    result.AnnounceLogMessage = std::format(
        "Player [{}] {} has picked up {}",
        Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
        point.GiverNickname,
        ItemNameFormatter::GetFormattedItemName(point.CustomData));

    return result;
}
