#include "Scp3114Strangling.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp3114Strangling::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp3114Strangling);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-3114 strangled a player";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-3114 strangled a player",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
