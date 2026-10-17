#include "PlayerHit.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerHit::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::PlayerHit);
    /*
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Was hit";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} was hit",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    */
    return result;
}
