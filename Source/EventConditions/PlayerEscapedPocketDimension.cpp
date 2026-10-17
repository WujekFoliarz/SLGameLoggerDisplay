#include "PlayerEscapedPocketDimension.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::PlayerEscapedPocketDimension::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = false;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (!point.Handled)
    {
        result.AnnounceLogMessage = std::format(
            "A Player [{}] {} escaped from the Pocket Dimension",
            Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
            point.GiverNickname);
    }

    return result;
}
