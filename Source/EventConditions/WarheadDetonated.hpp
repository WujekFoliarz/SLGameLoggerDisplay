#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::WarheadDetonated
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
