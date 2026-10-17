#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::ServerCompletingObjective
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
