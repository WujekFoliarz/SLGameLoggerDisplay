#include "Scp939Clawed.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp939Clawed::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp939Clawed);
    /*
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-939 clawed a player";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-939 clawed a player",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    */
    return result;
}
