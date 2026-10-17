#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace PlayerShot
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
