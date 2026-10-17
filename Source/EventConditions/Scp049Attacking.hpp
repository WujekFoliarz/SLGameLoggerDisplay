#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp049Attacking
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
