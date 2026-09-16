#include "GrenadeThrown.hpp"
#include <format>
#include <string>

ConditionChecker::ConditionCheckResult EventConditions::GrenadeThrown::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.IconColor = PointParams::GetRoleColor(point.GiverRole);
    result.Icon = PointParams::Icon::GrenadeThrown;
    
    if (point.Handled)
    {
        return result;
    }

    result.AnnounceLogMessage = std::format("Player {} has thrown a grenade", point.GiverNickname);

    return result;
}