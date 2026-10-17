#include "PlayerShot.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerShot::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.Icon = PointParams::Icon::GunFired;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);
    return result;
}
