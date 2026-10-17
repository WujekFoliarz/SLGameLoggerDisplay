#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace PlayerJoined
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
