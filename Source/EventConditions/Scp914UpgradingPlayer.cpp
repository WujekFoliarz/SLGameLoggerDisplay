#include "Scp914UpgradingPlayer.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp914UpgradingPlayer::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp914UpgradingPlayer);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            //result.AnnounceLogMessage = "SCP-914 upgraded a player";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} was teleported to SCP-914's output",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
