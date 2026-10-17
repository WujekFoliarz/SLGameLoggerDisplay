#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions::PlayerCalledElevator
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
