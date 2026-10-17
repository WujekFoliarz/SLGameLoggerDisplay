#include "PlayerBanned.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerBanned::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::PlayerBanned);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Was banned";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} was banned",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
