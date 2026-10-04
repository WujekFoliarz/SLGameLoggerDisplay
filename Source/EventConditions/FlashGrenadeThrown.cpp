#include "FlashGrenadeThrown.hpp"
#include <format>
#include "../PointParams.hpp"

ConditionChecker::ConditionCheckResult EventConditions::FlashGrenadeThrown::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.Icon = PointParams::Icon::FlashbangThrown;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);
    if (!point.Handled)
        result.AnnounceLogMessage = std::format("Player [{}] {} threw a flash grenade", Events::RoleTypeIdToStringColorFormatted(point.GiverRole), point.GiverNickname);
    return result;
}
