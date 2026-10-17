#include "Scp173PlacingTantrum.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp173PlacingTantrum::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp173PlacingTantrum);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-173 placed a tantrum";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-173 placed a tantrum",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
