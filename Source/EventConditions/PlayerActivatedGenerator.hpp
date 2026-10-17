#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions::PlayerActivatedGenerator
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
