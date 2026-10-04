#pragma once

#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace CIWave
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
