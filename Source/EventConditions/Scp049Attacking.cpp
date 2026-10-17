#include "Scp049Attacking.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp049Attacking::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp049Attacking);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-049 attacked";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-049 attacked",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
