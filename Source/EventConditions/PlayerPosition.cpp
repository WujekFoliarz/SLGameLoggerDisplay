#include "PlayerPosition.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerPosition::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    return result;
}