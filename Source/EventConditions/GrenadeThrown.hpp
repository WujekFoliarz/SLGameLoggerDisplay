#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace GrenadeThrown
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}