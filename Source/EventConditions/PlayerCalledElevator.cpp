#include "PlayerCalledElevator.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerCalledElevator::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        result.AnnounceLogMessage = std::format(
            "Player [{}] {} clicked on elevator button",
            Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
            point.GiverNickname);
    }

    return result;
}
