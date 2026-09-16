#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace PlayerDied
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}