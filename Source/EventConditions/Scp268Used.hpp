#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace Scp268Used
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}