#include "ItemPunching.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::ItemPunching::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::ItemPunching);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Punched";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} punched",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
