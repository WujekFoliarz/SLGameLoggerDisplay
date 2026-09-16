#include "PointParams.hpp"
#include "Events.hpp"
#include <cassert>
#include <print>
#include "Rooms.hpp"

bool Intialized = false;
static inline constexpr float kDefaultDecayRate = 0.5f;

inline static const std::unordered_map<Events::EventEnum, float> DecayRateMap{
    {Events::EventEnum::PlayerPosition, 0.4f},
    {Events::EventEnum::PlayerDied, 0.1f},
    {Events::EventEnum::GrenadeThrown, 0.1f},
    {Events::EventEnum::GrenadeExploded, 0.1f},
    {Events::EventEnum::PlayerEscaped, 0.1f},
    {Events::EventEnum::PlayerEscorted, 0.1f},
    {Events::EventEnum::MicroHidFiring, 0.1f},
    {Events::EventEnum::MicroHidCharging, 0.1f},
    {Events::EventEnum::MicroHidCanceledCharging, 0.1f},
    {Events::EventEnum::DoorOpened, 2.0f},
    {Events::EventEnum::DoorClosed, 2.0f},
    {Events::EventEnum::Room, 0.00000000000000000000001f}};

inline static const std::unordered_map<Events::RoleTypeId, Color> RoleColorMap{
    {Events::RoleTypeId::None, GRAY},
    {Events::RoleTypeId::Scp173, RED},
    {Events::RoleTypeId::ClassD, ORANGE},
    {Events::RoleTypeId::Spectator, GRAY},
    {Events::RoleTypeId::Scp106, RED},
    {Events::RoleTypeId::NtfSpecialist, {173, 216, 230, 255}},
    {Events::RoleTypeId::Scp049, RED},
    {Events::RoleTypeId::Scientist, YELLOW},
    {Events::RoleTypeId::Scp079, RED},
    {Events::RoleTypeId::ChaosConscript, {144, 238, 144, 255}},
    {Events::RoleTypeId::Scp096, RED},
    {Events::RoleTypeId::Scp0492, RED},
    {Events::RoleTypeId::NtfSergeant, {43, 118, 186, 255}},
    {Events::RoleTypeId::NtfCaptain, {3, 80, 150, 255}},
    {Events::RoleTypeId::NtfPrivate, {92, 153, 209, 255}},
    {Events::RoleTypeId::Tutorial, PINK},
    {Events::RoleTypeId::FacilityGuard, {83, 104, 120, 255}},
    {Events::RoleTypeId::Scp939, RED},
    {Events::RoleTypeId::CustomRole, BROWN},
    {Events::RoleTypeId::ChaosRifleman, {51, 122, 44, 255}},
    {Events::RoleTypeId::ChaosMarauder, {25, 163, 55, 255}},
    {Events::RoleTypeId::ChaosRepressor, {75, 114, 72, 255}},
    {Events::RoleTypeId::Scp3114, RED},
    {Events::RoleTypeId::Destroyed, GRAY},
    {Events::RoleTypeId::Flamingo, PURPLE},
    {Events::RoleTypeId::AlphaFlamingo, PURPLE},
    {Events::RoleTypeId::ZombieFlamingo, PURPLE},
    {Events::RoleTypeId::NtfFlamingo, PURPLE},
    {Events::RoleTypeId::ChaosFlamingo, PURPLE},
};

inline static const std::unordered_map<Events::EventEnum, Color> EventColorMap{
    {Events::EventEnum::None, GRAY},
    {Events::EventEnum::Room, PURPLE},
    {Events::EventEnum::PlayerDied, RED},
    {Events::EventEnum::NtfWave, DARKBLUE},
    {Events::EventEnum::NtfMiniWave, BLUE},
    {Events::EventEnum::CIWave, DARKGREEN},
    {Events::EventEnum::CIMiniWave, GREEN},
};

inline static std::unordered_map<PointParams::Icon, Texture2D> EventIconsTextureMap;

void PointParams::Initialize()
{
    if (Intialized)
    {
        return;
    }

    for (int i = 1; i < (int)PointParams::Icon::Count; i++)
    {
        Texture2D texture = LoadTexture(std::string(RESOURCE_PATH "EventIcons/" + PointParams::IconToString((PointParams::Icon)i) + ".png").c_str());
        if (IsTextureValid(texture))
        {
            EventIconsTextureMap.emplace((PointParams::Icon)i, std::move(texture));
        }
    }

    Intialized = true;
}

float PointParams::GetDecayRate(Events::EventEnum eventEnum)
{
    if (auto it = DecayRateMap.find(eventEnum); it != DecayRateMap.end())
    {
        return it->second;
    }

    return kDefaultDecayRate;
}

Color PointParams::GetRoleColor(Events::RoleTypeId roleTypeId)
{
    if (auto it = RoleColorMap.find(roleTypeId); it != RoleColorMap.end())
    {
        return it->second;
    }

    return GRAY;
}

Color PointParams::GetEventColor(Events::EventEnum eventEnum)
{
    if (auto it = EventColorMap.find(eventEnum); it != EventColorMap.end())
    {
        return it->second;
    }

    return GRAY;
}

Texture2D *PointParams::GetIconTexture(Icon icon)
{
    assert(Intialized);

    if (auto it = EventIconsTextureMap.find(icon); it != EventIconsTextureMap.end())
    {
        return &it->second;
    }

    return nullptr;
}
