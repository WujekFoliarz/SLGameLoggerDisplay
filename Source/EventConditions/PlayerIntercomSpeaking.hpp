#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::PlayerIntercomSpeaking
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
