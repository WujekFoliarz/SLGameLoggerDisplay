#include "PlayerKicking.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerKicking::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::PlayerKicking);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Kicked a player";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} kicked a player",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
