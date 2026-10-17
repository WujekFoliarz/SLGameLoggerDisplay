#include "Scp096Enraging.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp096Enraging::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp096Enraging);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-096 became enraged";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-096 became enraged",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
