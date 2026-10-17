#include "WarheadStarting.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::WarheadStarting::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::WarheadStarting);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "The warhead sequence started";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} started the warhead sequence",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
