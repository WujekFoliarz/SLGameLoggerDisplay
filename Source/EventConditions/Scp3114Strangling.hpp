#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp3114Strangling
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
