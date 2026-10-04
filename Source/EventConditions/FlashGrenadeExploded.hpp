#pragma once

#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace FlashGrenadeExploded
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
