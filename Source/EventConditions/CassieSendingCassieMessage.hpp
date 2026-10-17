#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::CassieSendingCassieMessage
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
