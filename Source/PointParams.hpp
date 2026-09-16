#pragma once

#include <unordered_map>
#include "raylib.h"
#include <string>
#include <variant>

namespace Events
{
    enum class EventEnum;
    enum class RoleTypeId;
}

namespace Rooms
{
    enum class LczRoom;
    enum class HczRoom;
    enum class SurfaceRoom;
}

namespace PointParams
{
    enum class Icon
    {
        None,
        PlayerEliminated,
        SpawnWave,
        SCP268Used,
        SCP268Expired,
        PlayerEscaped,
        PlayerEscorted,
        GrenadeThrown,
        PlayerShot,
        NeckSnapped,
        GrenadeExploded,
        DoorOpened,
        DoorClosed,
        MicroHidFiring,
        MicroHidCharging,
        MicroHidCanceledCharging,
        PlayerPosition,
        Count
    };

    constexpr std::string IconToString(Icon icon)
    {
        switch (icon)
        {
        case Icon::None:
            return "None";
        case Icon::PlayerEliminated:
            return "PlayerEliminated";
        case Icon::SpawnWave:
            return "SpawnWave";
        case Icon::SCP268Used:
            return "SCP268Used";
        case Icon::SCP268Expired:
            return "SCP268Expired";
        case Icon::PlayerEscaped:
            return "PlayerEscaped";
        case Icon::PlayerEscorted:
            return "PlayerEscorted";
        case Icon::GrenadeThrown:
            return "GrenadeThrown";
        case Icon::PlayerShot:
            return "PlayerShot";
        case Icon::NeckSnapped:
            return "NeckSnapped";
        case Icon::GrenadeExploded:
            return "GrenadeExploded";
        case Icon::DoorOpened:
            return "DoorOpened";
        case Icon::DoorClosed:
            return "DoorClosed";
        case Icon::MicroHidFiring:
            return "MicroHidFiring";
        case Icon::MicroHidCharging:
            return "MicroHidCharging";
        case Icon::MicroHidCanceledCharging:
            return "MicroHidCanceledCharging";
        case Icon::PlayerPosition:
            return "PlayerPosition";
        }

        return "Unknown";
    }

    void Initialize();
    float GetDecayRate(Events::EventEnum eventEnum);
    Color GetRoleColor(Events::RoleTypeId roleTypeId);
    Color GetEventColor(Events::EventEnum eventEnum);
    Texture2D *GetIconTexture(Icon icon);
}