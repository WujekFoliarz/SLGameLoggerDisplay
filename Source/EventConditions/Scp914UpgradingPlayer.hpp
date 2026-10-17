#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp914UpgradingPlayer
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
