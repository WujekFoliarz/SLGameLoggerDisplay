#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions::PlayerSentToPocketDimension
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
