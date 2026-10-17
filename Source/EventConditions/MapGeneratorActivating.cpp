#include "MapGeneratorActivating.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::MapGeneratorActivating::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::MapGeneratorActivating);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Activated a generator";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} activated a generator",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
