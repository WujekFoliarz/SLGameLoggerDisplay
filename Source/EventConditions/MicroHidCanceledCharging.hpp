#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace MicroHidCanceledCharging
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}