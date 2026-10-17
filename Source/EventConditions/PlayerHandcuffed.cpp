#include "PlayerHandcuffed.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerHandcuffed::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        if (point.ReceiverNickname.empty())
        {
            result.AnnounceLogMessage = std::format(
                "A Player [{}] {} handcuffed",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "A Player [{}] {} handcuffed Player [{}] {}",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname,
                Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole),
                point.ReceiverNickname);
        }
    }

    return result;
}
