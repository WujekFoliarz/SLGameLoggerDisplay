#include "MapAnnouncingScpTermination.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::MapAnnouncingScpTermination::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::MapAnnouncingScpTermination);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Announced SCP termination";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Announced SCP termination [{}] {}",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
