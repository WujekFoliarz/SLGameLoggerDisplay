#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::PlayerKicking
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
