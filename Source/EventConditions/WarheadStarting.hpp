#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::WarheadStarting
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
