#include "Scp2536GrantingGift.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp2536GrantingGift::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp2536GrantingGift);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-2536 granted a gift";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-2536 granted a gift",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
