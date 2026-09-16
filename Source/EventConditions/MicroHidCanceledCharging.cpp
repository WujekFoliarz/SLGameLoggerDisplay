#include "MicroHidCanceledCharging.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::MicroHidCanceledCharging::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::MicroHidCanceledCharging;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (point.Handled)
    {
        return result;
    }

    result.AnnounceLogMessage = std::format("Player [{}] {} has cancelled charging MicroHID", Events::RoleTypeIdToStringColorFormatted(point.GiverRole), point.GiverNickname);

    return result;
}