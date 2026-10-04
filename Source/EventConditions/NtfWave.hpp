#pragma once

#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace NtfWave
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
