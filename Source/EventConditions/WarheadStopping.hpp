#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::WarheadStopping
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
