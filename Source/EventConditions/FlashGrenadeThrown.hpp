#pragma once

#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions
{
    namespace FlashGrenadeThrown
    {
        ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
    }
}
