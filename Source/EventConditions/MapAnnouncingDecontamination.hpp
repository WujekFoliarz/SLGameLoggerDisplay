#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::MapAnnouncingDecontamination
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
