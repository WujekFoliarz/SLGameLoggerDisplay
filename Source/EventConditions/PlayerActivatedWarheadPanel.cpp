#include "PlayerActivatedWarheadPanel.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerActivatedWarheadPanel::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        result.AnnounceLogMessage = std::format(
            "A Player [{}] {} activated the Alpha Warhead panel",
            Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
            point.GiverNickname);
    }

    return result;
}
