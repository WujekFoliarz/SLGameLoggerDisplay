#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::WarheadDeadmanSwitchInitiating
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
