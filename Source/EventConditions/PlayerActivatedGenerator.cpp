#include "PlayerActivatedGenerator.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerActivatedGenerator::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        result.AnnounceLogMessage = std::format(
            "A Player [{}] {} activated a generator",
            Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
            point.GiverNickname);
    }

    return result;
}
