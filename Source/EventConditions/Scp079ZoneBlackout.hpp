#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp079ZoneBlackout
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
