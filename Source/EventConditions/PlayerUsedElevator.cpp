#include "PlayerUsedElevator.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerUsedElevator::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        result.AnnounceLogMessage = std::format(
            "A Player [{}] {} used an elevator from inside",
            Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
            point.GiverNickname);
    }

    return result;
}
