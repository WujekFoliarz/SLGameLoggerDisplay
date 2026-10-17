#include "Scp244OpeningScp244.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp244OpeningScp244::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp244OpeningScp244);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-244 was opened";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-244 was opened",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
