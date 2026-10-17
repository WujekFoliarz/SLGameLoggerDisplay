#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace PlayerHurt
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
