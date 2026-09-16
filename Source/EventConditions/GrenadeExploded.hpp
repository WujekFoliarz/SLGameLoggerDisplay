#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace GrenadeExploded
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}