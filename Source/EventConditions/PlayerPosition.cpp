#include "PlayerPosition.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerPosition::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    return result;
}