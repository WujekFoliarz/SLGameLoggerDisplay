#include "Scp106Attacking.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp106Attacking::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp106Attacking);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-106 attacked";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-106 attacked",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
