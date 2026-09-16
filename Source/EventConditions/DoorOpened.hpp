#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace DoorOpened
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}