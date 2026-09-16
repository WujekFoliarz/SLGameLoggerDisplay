#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace PlayerPosition
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}