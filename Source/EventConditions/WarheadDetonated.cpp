#include "WarheadDetonated.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::WarheadDetonated::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::WarheadDetonated);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "The warhead detonated";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} detonated the warhead",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
