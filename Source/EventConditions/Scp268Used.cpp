#include "Scp268Used.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp268Used::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::SCP268Used;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (point.Handled)
    {
        return result;
    }

    result.AnnounceLogMessage = std::format("Player [{}] {} has used SCP-268", Events::RoleTypeIdToString(point.GiverRole), point.GiverNickname);

    return result;
}