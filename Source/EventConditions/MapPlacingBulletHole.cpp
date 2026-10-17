#include "MapPlacingBulletHole.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::MapPlacingBulletHole::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);
    result.Icon = PointParams::Icon::BulletHole;
    return result;
}
