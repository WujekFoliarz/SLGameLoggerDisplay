#include "Scp079ZoneBlackout.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp079ZoneBlackout::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp079ZoneBlackout);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-079 blacked out a zone";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-079 blacked out a zone",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
