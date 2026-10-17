#pragma once

#include "../ConditionChecker.hpp"

namespace EventConditions::ServerReportingCheater
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
