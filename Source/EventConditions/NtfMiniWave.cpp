#include "NtfMiniWave.hpp"

ConditionChecker::ConditionCheckResult EventConditions::NtfMiniWave::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetEventColor(point.Event);
    if (!point.Handled)
        result.AnnounceLogMessage = "MTF mini-wave spawned";
    return result;
}
