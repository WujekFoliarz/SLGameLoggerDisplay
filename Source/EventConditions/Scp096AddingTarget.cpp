#include "Scp096AddingTarget.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp096AddingTarget::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp096AddingTarget);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-096 acquired a target";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-096 acquired a target",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
