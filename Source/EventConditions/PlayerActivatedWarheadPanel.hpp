#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions::PlayerActivatedWarheadPanel
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
