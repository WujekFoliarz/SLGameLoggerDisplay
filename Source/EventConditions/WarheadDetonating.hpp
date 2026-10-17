#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::WarheadDetonating
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
