#include "PickingUpItem.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PickingUpItem::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (point.Handled)
    {
        return result;
    }

    //result.AnnounceLogMessage = std::format("Player [{}] {} has picked up {}", Events::RoleTypeIdToString(point.Role), point.GiverNickname, point.CustomData);

    return result;
}