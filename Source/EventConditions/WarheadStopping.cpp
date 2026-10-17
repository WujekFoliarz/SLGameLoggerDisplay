#include "WarheadStopping.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::WarheadStopping::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::WarheadStopping);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "The warhead sequence stopped";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} stopped the warhead sequence",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
