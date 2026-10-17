#pragma once
#include "../ConditionChecker.hpp"
#include "../Events.hpp"

namespace EventConditions::PlayerPressedEmergencyDoorButton
{
    ConditionChecker::ConditionCheckResult GetResult(const Events::Point &point);
}
