#include "Scp939PlacingAmnesticCloud.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp939PlacingAmnesticCloud::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp939PlacingAmnesticCloud);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-939 placed an amnestic cloud";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-939 placed an amnestic cloud",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
