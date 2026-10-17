#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::ServerRespawnedTeam
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
