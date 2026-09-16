#include "MicroHidCharging.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::MicroHidCharging::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::MicroHidCharging;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (point.Handled)
    {
        return result;
    }

    result.AnnounceLogMessage = std::format("Player [{}] {} has started charging MicroHID", Events::RoleTypeIdToStringColorFormatted(point.GiverRole), point.ReceiverNickname);

    return result;
}