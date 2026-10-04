#include "PickingUpItem.hpp"

#include <algorithm>
#include <array>
#include <format>
#include <string_view>

namespace
{
    constexpr std::string_view kNone = "None";
    constexpr std::string_view kKeycardJanitor = "KeycardJanitor";
    constexpr std::string_view kKeycardScientist = "KeycardScientist";
    constexpr std::string_view kKeycardResearchCoordinator = "KeycardResearchCoordinator";
    constexpr std::string_view kKeycardZoneManager = "KeycardZoneManager";
    constexpr std::string_view kKeycardGuard = "KeycardGuard";
    constexpr std::string_view kKeycardMTFPrivate = "KeycardMTFPrivate";
    constexpr std::string_view kKeycardContainmentEngineer = "KeycardContainmentEngineer";
    constexpr std::string_view kKeycardMTFOperative = "KeycardMTFOperative";
    constexpr std::string_view kKeycardMTFCaptain = "KeycardMTFCaptain";
    constexpr std::string_view kKeycardFacilityManager = "KeycardFacilityManager";
    constexpr std::string_view kKeycardChaosInsurgency = "KeycardChaosInsurgency";
    constexpr std::string_view kKeycardO5 = "KeycardO5";
    constexpr std::string_view kRadio = "Radio";
    constexpr std::string_view kGunCOM15 = "GunCOM15";
    constexpr std::string_view kMedkit = "Medkit";
    constexpr std::string_view kFlashlight = "Flashlight";
    constexpr std::string_view kMicroHID = "MicroHID";
    constexpr std::string_view kSCP500 = "SCP500";
    constexpr std::string_view kSCP207 = "SCP207";
    constexpr std::string_view kAmmo12gauge = "Ammo12gauge";
    constexpr std::string_view kGunE11SR = "GunE11SR";
    constexpr std::string_view kGunCrossvec = "GunCrossvec";
    constexpr std::string_view kAmmo556x45 = "Ammo556x45";
    constexpr std::string_view kGunFSP9 = "GunFSP9";
    constexpr std::string_view kGunLogicer = "GunLogicer";
    constexpr std::string_view kGrenadeHE = "GrenadeHE";
    constexpr std::string_view kGrenadeFlash = "GrenadeFlash";
    constexpr std::string_view kAmmo44cal = "Ammo44cal";
    constexpr std::string_view kAmmo762x39 = "Ammo762x39";
    constexpr std::string_view kAmmo9x19 = "Ammo9x19";
    constexpr std::string_view kGunCOM18 = "GunCOM18";
    constexpr std::string_view kSCP018 = "SCP018";
    constexpr std::string_view kSCP268 = "SCP268";
    constexpr std::string_view kAdrenaline = "Adrenaline";
    constexpr std::string_view kPainkillers = "Painkillers";
    constexpr std::string_view kCoin = "Coin";
    constexpr std::string_view kArmorLight = "ArmorLight";
    constexpr std::string_view kArmorCombat = "ArmorCombat";
    constexpr std::string_view kArmorHeavy = "ArmorHeavy";
    constexpr std::string_view kGunRevolver = "GunRevolver";
    constexpr std::string_view kGunAK = "GunAK";
    constexpr std::string_view kGunShotgun = "GunShotgun";
    constexpr std::string_view kSCP330 = "SCP330";
    constexpr std::string_view kSCP2176 = "SCP2176";
    constexpr std::string_view kSCP244a = "SCP244a";
    constexpr std::string_view kSCP244b = "SCP244b";
    constexpr std::string_view kSCP1853 = "SCP1853";
    constexpr std::string_view kParticleDisruptor = "ParticleDisruptor";
    constexpr std::string_view kGunCom45 = "GunCom45";
    constexpr std::string_view kSCP1576 = "SCP1576";
    constexpr std::string_view kJailbird = "Jailbird";
    constexpr std::string_view kAntiSCP207 = "AntiSCP207";
    constexpr std::string_view kGunFRMG0 = "GunFRMG0";
    constexpr std::string_view kGunA7 = "GunA7";
    constexpr std::string_view kLantern = "Lantern";
    constexpr std::string_view kSCP1344 = "SCP1344";
    constexpr std::string_view kSnowball = "Snowball";
    constexpr std::string_view kCoal = "Coal";
    constexpr std::string_view kSpecialCoal = "SpecialCoal";
    constexpr std::string_view kSCP1507Tape = "SCP1507Tape";
    constexpr std::string_view kDebugRagdollMover = "DebugRagdollMover";
    constexpr std::string_view kSurfaceAccessPass = "SurfaceAccessPass";
    constexpr std::string_view kGunSCP127 = "GunSCP127";
    constexpr std::string_view kKeycardCustomTaskForce = "KeycardCustomTaskForce";
    constexpr std::string_view kKeycardCustomSite02 = "KeycardCustomSite02";
    constexpr std::string_view kKeycardCustomManagement = "KeycardCustomManagement";
    constexpr std::string_view kKeycardCustomMetalCase = "KeycardCustomMetalCase";
    constexpr std::string_view kMarshmallowItem = "MarshmallowItem";
    constexpr std::string_view kSCP1509 = "SCP1509";
    constexpr std::string_view kScp021J = "Scp021J";

    constexpr std::array kFormattedItemNames{
        std::pair{kNone, "None"},
        std::pair{kKeycardJanitor, "Janitor Keycard"},
        std::pair{kKeycardScientist, "Scientist Keycard"},
        std::pair{kKeycardResearchCoordinator, "Research Coordinator Keycard"},
        std::pair{kKeycardZoneManager, "Zone Manager Keycard"},
        std::pair{kKeycardGuard, "Guard Keycard"},
        std::pair{kKeycardMTFPrivate, "MTF Private Keycard"},
        std::pair{kKeycardContainmentEngineer, "Containment Engineer Keycard"},
        std::pair{kKeycardMTFOperative, "MTF Operative Keycard"},
        std::pair{kKeycardMTFCaptain, "MTF Captain Keycard"},
        std::pair{kKeycardFacilityManager, "Facility Manager Keycard"},
        std::pair{kKeycardChaosInsurgency, "Chaos Insurgency Keycard"},
        std::pair{kKeycardO5, "O5 Keycard"},
        std::pair{kRadio, "Radio"},
        std::pair{kGunCOM15, "COM-15"},
        std::pair{kMedkit, "Medkit"},
        std::pair{kFlashlight, "Flashlight"},
        std::pair{kMicroHID, "Micro HID"},
        std::pair{kSCP500, "SCP-500"},
        std::pair{kSCP207, "SCP-207"},
        std::pair{kAmmo12gauge, "12-Gauge Ammo"},
        std::pair{kGunE11SR, "E-11 SR"},
        std::pair{kGunCrossvec, "Crossvec"},
        std::pair{kAmmo556x45, "5.56x45mm Ammo"},
        std::pair{kGunFSP9, "FSP-9"},
        std::pair{kGunLogicer, "Logicer"},
        std::pair{kGrenadeHE, "HE Grenade"},
        std::pair{kGrenadeFlash, "Flash Grenade"},
        std::pair{kAmmo44cal, ".44 Caliber Ammo"},
        std::pair{kAmmo762x39, "7.62x39mm Ammo"},
        std::pair{kAmmo9x19, "9x19mm Ammo"},
        std::pair{kGunCOM18, "COM-18"},
        std::pair{kSCP018, "SCP-018"},
        std::pair{kSCP268, "SCP-268"},
        std::pair{kAdrenaline, "Adrenaline"},
        std::pair{kPainkillers, "Painkillers"},
        std::pair{kCoin, "Coin"},
        std::pair{kArmorLight, "Light Armor"},
        std::pair{kArmorCombat, "Combat Armor"},
        std::pair{kArmorHeavy, "Heavy Armor"},
        std::pair{kGunRevolver, "Revolver"},
        std::pair{kGunAK, "AK"},
        std::pair{kGunShotgun, "Shotgun"},
        std::pair{kSCP330, "SCP-330"},
        std::pair{kSCP2176, "SCP-2176"},
        std::pair{kSCP244a, "SCP-244-A"},
        std::pair{kSCP244b, "SCP-244-B"},
        std::pair{kSCP1853, "SCP-1853"},
        std::pair{kParticleDisruptor, "Particle Disruptor"},
        std::pair{kGunCom45, "COM-45"},
        std::pair{kSCP1576, "SCP-1576"},
        std::pair{kJailbird, "Jailbird"},
        std::pair{kAntiSCP207, "Anti-SCP-207"},
        std::pair{kGunFRMG0, "FR-MG-0"},
        std::pair{kGunA7, "A-7"},
        std::pair{kLantern, "Lantern"},
        std::pair{kSCP1344, "SCP-1344"},
        std::pair{kSnowball, "Snowball"},
        std::pair{kCoal, "Coal"},
        std::pair{kSpecialCoal, "Special Coal"},
        std::pair{kSCP1507Tape, "SCP-1507 Tape"},
        std::pair{kDebugRagdollMover, "Debug Ragdoll Mover"},
        std::pair{kSurfaceAccessPass, "Surface Access Pass"},
        std::pair{kGunSCP127, "SCP-127"},
        std::pair{kKeycardCustomTaskForce, "Custom Task Force Keycard"},
        std::pair{kKeycardCustomSite02, "Custom Site-02 Keycard"},
        std::pair{kKeycardCustomManagement, "Custom Management Keycard"},
        std::pair{kKeycardCustomMetalCase, "Custom Metal Case Keycard"},
        std::pair{kMarshmallowItem, "Marshmallow"},
        std::pair{kSCP1509, "SCP-1509"},
        std::pair{kScp021J, "SCP-021-J"},
    };

    std::string_view GetFormattedItemName(std::string_view itemType)
    {
        const auto item = std::find_if(
            kFormattedItemNames.begin(),
            kFormattedItemNames.end(),
            [itemType](const auto &entry)
            { return entry.first == itemType; });
        return item != kFormattedItemNames.end() ? item->second : itemType;
    }

    bool ShouldDisplayLogMessage(std::string_view itemType)
    {
        if (itemType.substr(0, 7) == "Keycard")
            return true;

        constexpr std::array rareItems{
            kSurfaceAccessPass,
            kMicroHID,
            kSCP018,
            kSCP500,
            kSCP207,
            kSCP268,
            kSCP330,
            kSCP2176,
            kSCP244a,
            kSCP244b,
            kSCP1853,
            kParticleDisruptor,
            kSCP1576,
            kJailbird,
            kGunFRMG0,
            kGunA7,
            kSCP1344,
            kSpecialCoal,
            kSCP1507Tape,
            kGunSCP127,
            kSCP1509,
            kScp021J,
        };

        return std::find(rareItems.begin(), rareItems.end(), itemType) != rareItems.end();
    }
}

ConditionChecker::ConditionCheckResult EventConditions::PickingUpItem::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.UseDotInsteadOfIcon = true;
    result.IconColor = PointParams::GetRoleColor(point.GiverRole);

    if (point.Handled)
        return result;

    if (!ShouldDisplayLogMessage(point.CustomData))
        return result;

    result.AnnounceLogMessage = std::format(
        "Player [{}] {} has picked up {}",
        Events::RoleTypeIdToStringColorFormatted(point.GiverRole),
        point.GiverNickname,
        GetFormattedItemName(point.CustomData));

    return result;
}
