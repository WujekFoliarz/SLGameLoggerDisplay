#include "BallThrown.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::BallThrown::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);
    if (!point.Handled)
        result.AnnounceLogMessage = std::format("Player {} threw a ball", point.GiverNickname);
    return result;
}
