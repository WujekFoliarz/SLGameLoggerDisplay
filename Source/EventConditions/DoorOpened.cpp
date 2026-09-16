#include "DoorOpened.hpp"

ConditionChecker::ConditionCheckResult EventConditions::DoorOpened::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::DoorOpened;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    return result;
}