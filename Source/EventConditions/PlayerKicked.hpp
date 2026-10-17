#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::PlayerKicked
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
