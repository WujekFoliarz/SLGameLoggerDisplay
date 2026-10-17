#include "WarheadDeadmanSwitchInitiating.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::WarheadDeadmanSwitchInitiating::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::WarheadDeadmanSwitchInitiating);
    if (!point.Handled)
    {
        result.AnnounceLogMessage = "The warhead deadman switch was initiated";
    }
    return result;
}
