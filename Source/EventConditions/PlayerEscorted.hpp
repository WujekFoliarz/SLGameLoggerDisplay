#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace PlayerEscorted
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}