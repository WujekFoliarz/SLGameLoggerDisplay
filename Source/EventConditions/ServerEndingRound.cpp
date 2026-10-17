#include "ServerEndingRound.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::ServerEndingRound::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::ServerEndingRound);
    /*
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "The round is ending";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} is ending the round",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
        */
    return result;
}
