#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::PlayerBanned
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
