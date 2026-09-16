#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace Scp268Expired
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}