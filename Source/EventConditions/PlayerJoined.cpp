#include "PlayerJoined.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerJoined::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        if (point.GiverRole == Events::RoleTypeId::None || Events::RoleTypeIdToString(point.GiverRole) == "UNKNOWN")
        {
            result.AnnounceLogMessage = std::format("Player {} joined the server", point.GiverNickname);
        }
        else
        {
            result.AnnounceLogMessage = std::format("Player [{}] {} joined the server", Events::RoleTypeIdToStringColorFormatted(point.GiverRole), point.GiverNickname);
        }
    }

    return result;
}
