#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp106Attacking
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
