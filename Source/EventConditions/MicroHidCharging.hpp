#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace MicroHidCharging
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}