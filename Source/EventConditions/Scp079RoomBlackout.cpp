#include "Scp079RoomBlackout.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::Scp079RoomBlackout::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::Scp079RoomBlackout);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "SCP-079 blacked out a room";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} SCP-079 blacked out a room",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
