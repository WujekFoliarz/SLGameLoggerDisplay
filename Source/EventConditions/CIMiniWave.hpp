#pragma once

#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace CIMiniWave
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
