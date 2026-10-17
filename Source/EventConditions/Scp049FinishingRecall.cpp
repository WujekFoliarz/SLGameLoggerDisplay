#include "Scp049FinishingRecall.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp049FinishingRecall::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp049FinishingRecall);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-049 finished recalling a player";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-049 finished recalling a player",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
