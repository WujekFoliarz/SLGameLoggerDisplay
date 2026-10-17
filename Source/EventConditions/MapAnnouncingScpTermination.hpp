#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::MapAnnouncingScpTermination
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
