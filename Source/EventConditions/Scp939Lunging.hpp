#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp939Lunging
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
