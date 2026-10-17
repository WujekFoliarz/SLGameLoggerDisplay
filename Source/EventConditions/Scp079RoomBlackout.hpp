#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::Scp079RoomBlackout
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
