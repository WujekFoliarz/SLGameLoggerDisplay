#include "CIMiniWave.hpp"

ConditionChecker::ConditionCheckResult EventConditions::CIMiniWave::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetEventColor(point.Event);
    if (!point.Handled)
        result.AnnounceLogMessage = "Chaos Insurgency mini-wave spawned";
    return result;
}
