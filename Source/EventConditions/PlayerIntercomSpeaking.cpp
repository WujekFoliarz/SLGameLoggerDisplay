#include "PlayerIntercomSpeaking.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerIntercomSpeaking::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::PlayerIntercomSpeaking);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Spoke over the intercom";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} spoke over the intercom",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
