#include "FlashGrenadeExploded.hpp"
#include <format>

#include "../PointParams.hpp"

ConditionChecker::ConditionCheckResult EventConditions::FlashGrenadeExploded::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.Icon = PointParams::Icon::FlashbangExploded;
    result.IconColor = PointParams::GetRoleColor(point.ReceiverRole);
    if (!point.Handled)
    {
        result.AnnounceLogMessage = point.GiverNickname.empty()
                                        ? "Flash grenade exploded"
                                        : std::format("Flash grenade thrown by [{}] {} exploded", Events::RoleTypeIdToStringColorFormatted(point.GiverRole), point.GiverNickname);
    }
    return result;
}
