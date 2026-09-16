#include "PlayerEscaped.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerEscaped::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::PlayerEscaped;
    result.IconColor = PointParams::GetRoleColor(point.ReceiverRole);

    if (point.Handled)
    {
        return result;
    }

    result.AnnounceLogMessage = std::format("Player [{}] {} has escaped the Facility", Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole), point.ReceiverNickname);

    return result;
}