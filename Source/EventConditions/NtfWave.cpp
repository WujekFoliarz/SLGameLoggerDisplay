#include "NtfWave.hpp"

ConditionChecker::ConditionCheckResult EventConditions::NtfWave::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetEventColor(point.Event);
    if (!point.Handled)
        result.AnnounceLogMessage = "MTF wave spawned";
    return result;
}
