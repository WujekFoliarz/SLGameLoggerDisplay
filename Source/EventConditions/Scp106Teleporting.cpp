#include "Scp106Teleporting.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp106Teleporting::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp106Teleporting);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-106 teleported";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-106 teleported",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
