#include "PlayerHurt.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerHurt::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.ReceiverRole);

    /*
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} took damage ({})",
                Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole),
                point.ReceiverNickname,
                point.CustomData);
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} damaged Player [{}] {} ({})",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname,
                Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole),
                point.ReceiverNickname,
                point.CustomData);
        }
    }
    */

    return result;
}
