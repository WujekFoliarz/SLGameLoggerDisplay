#pragma once

#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace NtfMiniWave
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
