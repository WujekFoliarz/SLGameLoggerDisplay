#include "PlayerEscorted.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerEscorted::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::PlayerEscorted;
    result.IconColor = PointParams::GetRoleColor(point.ReceiverRole);

    if (point.Handled)
    {
        return result;
    }

    result.AnnounceLogMessage = std::format("Player [{}] {} has been escorted by [{}] {}", Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole), point.ReceiverNickname, Events::RoleTypeIdToStringColorFormatted(point.GiverRole), point.GiverNickname);

    return result;
}