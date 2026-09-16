#include "GrenadeExploded.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::GrenadeExploded::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::GrenadeExploded;
    result.IconColor = PointParams::GetRoleColor(point.ReceiverRole);

    if (point.Handled)
    {
        return result;
    }

    if (point.ReceiverNickname.empty())
    {
        result.AnnounceLogMessage = "Grenade has exploded";
    }
    else
    {
        result.AnnounceLogMessage = std::format("Grenade thrown by [{}] {} has exploded", Events::RoleTypeIdToString(point.GiverRole), point.GiverNickname);
    }

    return result;
}