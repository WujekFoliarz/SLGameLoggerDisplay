#include "Events.hpp"

std::string Events::RoleTypeIdToStringColorFormatted(Events::RoleTypeId role)
{
    Color color = PointParams::GetRoleColor(role);
    return std::format(" ${},{},{},{} {} $255,255,255,255 ", color.r, color.g, color.b, color.a, RoleTypeIdToString(role));
}

std::string Events::EventToString(EventEnum event)
{
    switch (event)
    {
    case EventEnum::None:
        return "None";
    case EventEnum::MapLCZ:
        return "MapLCZ";
    case EventEnum::MapHCZ:
        return "MapHCZ";
    case EventEnum::MapEZ:
        return "MapEZ";
    case EventEnum::PlayerPosition:
        return "PlayerPosition";
    case EventEnum::DoorClosed:
        return "DoorClosed";
    case EventEnum::DoorOpened:
        return "DoorOpened";
    case EventEnum::PlayerDied:
        return "PlayerDied";
    case EventEnum::NtfWave:
        return "NtfWave";
    case EventEnum::NtfMiniWave:
        return "NtfMiniWave";
    case EventEnum::CIWave:
        return "CIWave";
    case EventEnum::CIMiniWave:
        return "CIMiniWave";
    case EventEnum::BallThrown:
        return "BallThrown";
    case EventEnum::BallBounced:
        return "BallBounced";
    case EventEnum::HitByBall:
        return "HitByBall";
    case EventEnum::GrenadeThrown:
        return "GrenadeThrown";
    case EventEnum::GrenadeExploded:
        return "GrenadeExploded";
    case EventEnum::PickedUpItem:
        return "PickedUpItem";
    case EventEnum::DroppedItem:
        return "DroppedItem";
    case EventEnum::Room:
        return "Room";
    case EventEnum::PickingUpItem:
        return "PickingUpItem";
    case EventEnum::FlashGrenadeThrown:
        return "FlashGrenadeThrown";
    case EventEnum::FlashGrenadeExploded:
        return "FlashGrenadeExploded";
    case EventEnum::MicroHidCharging:
        return "MicroHidCharging";
    case EventEnum::MicroHidCanceledCharging:
        return "MicroHidCanceledCharging";
    case EventEnum::MicroHidFiring:
        return "MicroHidFiring";
    case EventEnum::PlayerEscaped:
        return "PlayerEscaped";
    case EventEnum::PlayerEscorted:
        return "PlayerEscorted";
    case EventEnum::SCP268Used:
        return "SCP268Used";
    case EventEnum::SCP268Expired:
        return "SCP268Expired";
    case EventEnum::NewTick:
        return "NewTick";
    case EventEnum::PlayerJoined:
        return "PlayerJoined";
    case EventEnum::PlayerLeft:
        return "PlayerLeft";
    case EventEnum::PlayerChangedRoles:
        return "PlayerChangedRoles";
    case EventEnum::Version:
        return "Version";
    case EventEnum::Count:
        return "Count";
    }

    return std::format("[{}]", (int)event);
}
