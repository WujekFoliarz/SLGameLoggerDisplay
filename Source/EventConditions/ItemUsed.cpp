#include "ItemUsed.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::ItemUsed::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        result.AnnounceLogMessage = std::format(
            "Player [{}] {} used {}",
            Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
            point.GiverNickname,
            point.CustomData);
    }

    return result;
}
