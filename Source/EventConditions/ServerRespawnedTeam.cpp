#include "ServerRespawnedTeam.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::ServerRespawnedTeam::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::ServerRespawnedTeam);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "A team respawned";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} respawned a team",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
