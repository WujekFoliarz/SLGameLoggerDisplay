#include "PlayerPressedEmergencyDoorButton.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerPressedEmergencyDoorButton::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        result.AnnounceLogMessage = std::format(
            "A Player [{}] {} pressed an emergency door button",
            Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
            point.GiverNickname);
    }

    return result;
}
