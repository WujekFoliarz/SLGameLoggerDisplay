#include "ConditionChecker.hpp"
#include "Events.hpp"

#include "EventConditions/PlayerPosition.hpp"
#include "EventConditions/PlayerDied.hpp"
#include "EventConditions/GrenadeThrown.hpp"
#include "EventConditions/GrenadeExploded.hpp"
#include "EventConditions/DoorOpened.hpp"
#include "EventConditions/DoorClosed.hpp"
#include "EventConditions/PlayerEscaped.hpp"
#include "EventConditions/PlayerEscorted.hpp"
#include "EventConditions/MicroHidFiring.hpp"
#include "EventConditions/MicroHidCharging.hpp"
#include "EventConditions/MicroHidCanceledCharging.hpp"
#include "EventConditions/Scp268Used.hpp"
#include "EventConditions/Scp268Expired.hpp"
#include "EventConditions/PickingUpItem.hpp"

#include <print>
#include <functional>

ConditionChecker::ConditionCheckResult ConditionChecker::GetResult(const Events::Point &point)
{
    using Handler = std::function<ConditionChecker::ConditionCheckResult(const Events::Point &)>;

    static const std::unordered_map<Events::EventEnum, Handler> handlers =
        {
            {Events::EventEnum::Room,
             [](const Events::Point &point)
             {
                 ConditionCheckResult result{};
                 // result.UseDotInsteadOfIcon = true;
                 // result.IconColor = PURPLE;
                 return result;
             }},
            {Events::EventEnum::PlayerPosition, &EventConditions::PlayerPosition::GetResult},
            {Events::EventEnum::PlayerDied, &EventConditions::PlayerDied::GetResult},
            {Events::EventEnum::GrenadeThrown, &EventConditions::GrenadeThrown::GetResult},
            {Events::EventEnum::GrenadeExploded, &EventConditions::GrenadeExploded::GetResult},
            {Events::EventEnum::DoorOpened, &EventConditions::DoorOpened::GetResult},
            {Events::EventEnum::DoorClosed, &EventConditions::DoorClosed::GetResult},
            {Events::EventEnum::PlayerEscaped, &EventConditions::PlayerEscaped::GetResult},
            {Events::EventEnum::PlayerEscorted, &EventConditions::PlayerEscorted::GetResult},
            {Events::EventEnum::MicroHidFiring, &EventConditions::MicroHidFiring::GetResult},
            {Events::EventEnum::MicroHidCharging, &EventConditions::MicroHidCharging::GetResult},
            {Events::EventEnum::MicroHidCanceledCharging, &EventConditions::MicroHidCanceledCharging::GetResult},
            {Events::EventEnum::SCP268Used, &EventConditions::Scp268Used::GetResult},
            {Events::EventEnum::SCP268Expired, &EventConditions::Scp268Expired::GetResult},
            {Events::EventEnum::PickingUpItem, &EventConditions::PickingUpItem::GetResult},
    };

    if (auto it = handlers.find(point.Event); it != handlers.end())
    {
        return it->second(point);
    }
    else
    {
        std::println("[ConditionChecker::GetResult] Missing handler for event {}", Events::EventToString(point.Event));
    }

    return ConditionCheckResult();
}