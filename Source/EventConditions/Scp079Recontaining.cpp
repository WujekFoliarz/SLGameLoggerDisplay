#include "Scp079Recontaining.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp079Recontaining::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp079Recontaining);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-079 recontainment began";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-079 recontainment began",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
