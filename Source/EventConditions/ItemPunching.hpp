#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::ItemPunching
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
