#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions::PlayerUsedElevator
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
