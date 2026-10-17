#include "MapAnnouncingDecontamination.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::MapAnnouncingDecontamination::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::MapAnnouncingDecontamination);
    if (!point.Handled)
    {
        result.AnnounceLogMessage = "Announced LCZ decontamination";
    }
    return result;
}
