#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::PlayerExplodingMicroHID
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
