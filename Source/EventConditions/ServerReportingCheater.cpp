#include "ServerReportingCheater.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::ServerReportingCheater::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::ServerReportingCheater);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "A cheater was reported";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} reported a cheater",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
