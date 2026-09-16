#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace MicroHidFiring
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}