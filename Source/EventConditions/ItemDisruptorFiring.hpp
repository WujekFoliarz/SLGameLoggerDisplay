#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::ItemDisruptorFiring
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
