#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions::PlayerEscapedPocketDimension
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
