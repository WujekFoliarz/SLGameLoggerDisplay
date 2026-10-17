#include "ServerCompletingObjective.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::ServerCompletingObjective::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::ServerCompletingObjective);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "An objective was completed";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} completed an objective",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
