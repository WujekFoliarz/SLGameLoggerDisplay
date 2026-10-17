#include "Scp244DamagingScp244.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp244DamagingScp244::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp244DamagingScp244);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-244 caused damage";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-244 caused damage",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
