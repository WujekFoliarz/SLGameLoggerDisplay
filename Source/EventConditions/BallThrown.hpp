#pragma once

#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace BallThrown
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
