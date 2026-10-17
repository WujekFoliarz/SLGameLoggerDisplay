#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp096AddingTarget
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
