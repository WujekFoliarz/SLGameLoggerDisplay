#include "ItemJailbirdChargeComplete.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::ItemJailbirdChargeComplete::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::ItemJailbirdChargeComplete);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Completed charging a jailbird";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} completed charging a jailbird",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
