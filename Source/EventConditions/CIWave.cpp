#include "CIWave.hpp"

ConditionChecker::ConditionCheckResult EventConditions::CIWave::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetEventColor(point.Event);
    if (!point.Handled)
        result.AnnounceLogMessage = "Chaos Insurgency wave spawned";
    return result;
}
