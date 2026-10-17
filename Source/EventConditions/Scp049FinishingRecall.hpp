#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp049FinishingRecall
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
