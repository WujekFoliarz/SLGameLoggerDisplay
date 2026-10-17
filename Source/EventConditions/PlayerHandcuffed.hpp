#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions::PlayerHandcuffed
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
