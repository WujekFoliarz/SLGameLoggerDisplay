#include "CassieSendingCassieMessage.hpp"
#include <format>

ConditionChecker::ConditionCheckResult EventConditions::CassieSendingCassieMessage::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};
    result.DontRender = true;
    result.IconColor = PointParams::GetEventColor(Events::EventEnum::CassieSendingCassieMessage);
    if (!point.Handled)
    {
        if (point.GiverNickname.empty())
        {
            result.AnnounceLogMessage = "Sent a CASSIE message";
        }
        else
        {
            result.AnnounceLogMessage = std::format(
                "Player [{}] {} sent a CASSIE message",
                Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
                point.GiverNickname);
        }
    }
    return result;
}
