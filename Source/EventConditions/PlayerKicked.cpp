#include "PlayerKicked.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerKicked::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::PlayerKicked);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Was kicked";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} was kicked",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
