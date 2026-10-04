#include "HitByBall.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::HitByBall::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetRoleColor(point.ReceiverRole);
    if (!point.Handled)
    {
        result.AnnounceLogMessage = point.GiverNickname.empty()
                                        ? std::format("Player [{}] {} was hit by a ball", Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole), point.ReceiverNickname)
                                        : std::format("Player [{}] {} hit [{}] {} with a ball", Events::RoleTypeIdToStringColorFormatted(point.GiverRole), point.GiverNickname, Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole), point.ReceiverNickname);
    }
    return result;
}
