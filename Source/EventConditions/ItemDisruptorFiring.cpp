#include "ItemDisruptorFiring.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::ItemDisruptorFiring::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::ItemDisruptorFiring);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Fired the disruptor";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} fired the disruptor",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
