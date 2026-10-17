#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace ItemUsed
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
