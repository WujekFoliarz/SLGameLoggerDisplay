#include "Scp939Lunging.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp939Lunging::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp939Lunging);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-939 lunged";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-939 lunged",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
