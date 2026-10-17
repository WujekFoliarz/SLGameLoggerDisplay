#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace DroppedItem
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
