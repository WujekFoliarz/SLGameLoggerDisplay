#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::ServerEndingRound
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
