#include "PlayerExplodingMicroHID.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerExplodingMicroHID::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::PlayerExplodingMicroHID);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Triggered a MicroHID explosion";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} triggered a MicroHID explosion",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
