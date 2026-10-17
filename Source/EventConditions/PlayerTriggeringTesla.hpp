#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::PlayerTriggeringTesla
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
