#include "PlayerTriggeringTesla.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerTriggeringTesla::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::PlayerTriggeringTesla);
    return result;
}
