#include "Scp079Recontained.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp079Recontained::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp079Recontained);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-079 was recontained";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-079 was recontained",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
