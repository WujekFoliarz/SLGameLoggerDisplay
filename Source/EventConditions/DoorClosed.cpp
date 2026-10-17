#include "DoorClosed.hpp"

ConditionChecker::ConditionCheckResult EventConditions::DoorClosed::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.Icon = PointParams::Icon::DoorClosed;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    return result;
}