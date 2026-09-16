#include "Scp268Expired.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp268Expired::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.Icon = PointParams::Icon::SCP268Expired;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (point.Handled)
    {
        return result;
    }

    result.AnnounceLogMessage = std::format("[{}] {}'s SCP-268 has expired", Events::RoleTypeIdToString(point.GiverRole), point.GiverNickname);

    return result;
}