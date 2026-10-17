#include "MapDecontaminating.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::MapDecontaminating::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::MapDecontaminating);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Started facility decontamination";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} started facility decontamination",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
