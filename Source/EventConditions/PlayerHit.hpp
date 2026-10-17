#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::PlayerHit
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
