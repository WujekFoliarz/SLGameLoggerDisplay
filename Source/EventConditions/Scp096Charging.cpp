#include "Scp096Charging.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp096Charging::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp096Charging);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-096 began charging";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-096 began charging",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
