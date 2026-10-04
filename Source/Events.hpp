#pragma once

#include <string>
#include <format>
#include "DamageType.hpp"
#include "PointParams.hpp"

namespace Events
{
    enum class RoleTypeId
    {
        None = -1,
        Scp173,
        ClassD,
        Spectator,
        Scp106,
        NtfSpecialist,
        Scp049,
        Scientist,
        Scp079,
        ChaosConscript,
        Scp096,
        Scp0492,
        NtfSergeant,
        NtfCaptain,
        NtfPrivate,
        Tutorial,
        FacilityGuard,
        Scp939,
        CustomRole,
        ChaosRifleman,
        ChaosMarauder,
        ChaosRepressor,
        Overwatch,
        Filmmaker,
        Scp3114,
        Destroyed,
        Flamingo,
        AlphaFlamingo,
        ZombieFlamingo,
        NtfFlamingo,
        ChaosFlamingo
    };

    constexpr std::string_view RoleTypeIdToString(RoleTypeId role)
    {
        switch (role)
        {
        case RoleTypeId::None:
            return "NONE";
        case RoleTypeId::Scp173:
            return "SCP-173";
        case RoleTypeId::ClassD:
            return "CLASS D";
        case RoleTypeId::Spectator:
            return "SPECTATOR";
        case RoleTypeId::Scp106:
            return "SCP-106";
        case RoleTypeId::NtfSpecialist:
            return "NTF SPECIALIST";
        case RoleTypeId::Scp049:
            return "SCP-049";
        case RoleTypeId::Scientist:
            return "SCIENTIST";
        case RoleTypeId::Scp079:
            return "SCP-079";
        case RoleTypeId::ChaosConscript:
            return "CHAOS CONSCRIPT";
        case RoleTypeId::Scp096:
            return "SCP-096";
        case RoleTypeId::Scp0492:
            return "SCP-049-2";
        case RoleTypeId::NtfSergeant:
            return "NTF SERGEANT";
        case RoleTypeId::NtfCaptain:
            return "NTF CAPTAIN";
        case RoleTypeId::NtfPrivate:
            return "NTF PRIVATE";
        case RoleTypeId::Tutorial:
            return "TUTORIAL";
        case RoleTypeId::FacilityGuard:
            return "FACILITY GUARD";
        case RoleTypeId::Scp939:
            return "SCP-939";
        case RoleTypeId::CustomRole:
            return "CUSTOM ROLE";
        case RoleTypeId::ChaosRifleman:
            return "CHAOS RIFLEMAN";
        case RoleTypeId::ChaosMarauder:
            return "CHAOS MARAUDER";
        case RoleTypeId::ChaosRepressor:
            return "CHAOS REPRESSOR";
        case RoleTypeId::Overwatch:
            return "OVERWATCH";
        case RoleTypeId::Filmmaker:
            return "FILMMAKER";
        case RoleTypeId::Scp3114:
            return "SCP-3114";
        case RoleTypeId::Destroyed:
            return "DESTROYED";
        case RoleTypeId::Flamingo:
            return "FLAMINGO";
        case RoleTypeId::AlphaFlamingo:
            return "ALPHA FLAMINGO";
        case RoleTypeId::ZombieFlamingo:
            return "ZOMBIE FLAMINGO";
        case RoleTypeId::NtfFlamingo:
            return "NTF FLAMINGO";
        case RoleTypeId::ChaosFlamingo:
            return "CHAOS FLAMINGO";
        }

        return "UNKNOWN";
    }

    std::string RoleTypeIdToStringColorFormatted(RoleTypeId role);

    enum class EventEnum
    {
        None,
        MapLCZ,
        MapHCZ,
        MapEZ,
        PlayerPosition,
        DoorClosed,
        DoorOpened,
        PlayerDied,
        NtfWave,
        NtfMiniWave,
        CIWave,
        CIMiniWave,
        BallThrown,
        BallBounced,
        HitByBall,
        GrenadeThrown,
        GrenadeExploded,
        PickedUpItem,
        DroppedItem,
        Room,
        PickingUpItem,
        FlashGrenadeThrown,
        FlashGrenadeExploded,
        MicroHidCharging,
        MicroHidCanceledCharging,
        MicroHidFiring,
        PlayerEscaped,
        PlayerEscorted,
        SCP268Used,
        SCP268Expired,
        NewTick, // Packet
        PlayerJoined,
        PlayerLeft,
        PlayerChangedRoles,
        Version,
        Count
    };

    std::string EventToString(EventEnum event);

    struct Point
    {
        int Tick = 0;
        Vector3 Position{};
        Quaternion Rotation{};
        float Opacity = 1.0f;
        EventEnum Event;
        RoleTypeId GiverRole = RoleTypeId::None;
        RoleTypeId ReceiverRole = RoleTypeId::None;
        std::string GiverNickname = "";
        std::string ReceiverNickname = "";
        std::string CustomData = "";
        PointParams::Icon Icon = PointParams::Icon::None;
        bool UseDotInsteadOfIcon = false;
        Color IconColor = WHITE;
        bool Handled = false;
        Damage::Type DmgType = Damage::Type::Unknown;
        int Id = 0;
    };
}