#include "PlayerSentToPocketDimension.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerSentToPocketDimension::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        if (point.ReceiverNickname.empty())
        {
            result.AnnounceLogMessage = std::format(
                "A Player [{}] {} sent to the Pocket Dimension",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "A Player [{}] {} sent to the Pocket Dimension Player [{}] {}",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname,
                Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole),
                point.ReceiverNickname);
        }
    }

    return result;
}
