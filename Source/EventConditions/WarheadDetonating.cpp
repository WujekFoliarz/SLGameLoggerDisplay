#include "WarheadDetonating.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::WarheadDetonating::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::WarheadDetonating);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "The warhead began detonating";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} began detonating the warhead",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
