#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp106Teleporting
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
