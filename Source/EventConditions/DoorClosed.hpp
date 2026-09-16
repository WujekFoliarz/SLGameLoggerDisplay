#pragma once
#include "../Events.hpp"
#include "../ConditionChecker.hpp"

namespace EventConditions
{
    namespace DoorClosed
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}