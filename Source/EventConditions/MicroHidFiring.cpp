#include "MicroHidFiring.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::MicroHidFiring::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::MicroHidFiring;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (point.Handled)
    {
        return result;
    }

    result.AnnounceLogMessage = std::format("Player [{}] {} has started firing MicroHID", Events::RoleTypeIdToStringColorFormatted(point.GiverRole), point.GiverNickname);

    return result;
}