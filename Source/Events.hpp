#pragma once

#include <cstdint>
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
        PlayerHurt,
        PlayerShot,
        ItemUsed,
        ReservedPlayerActionEventId,
        ReservedEventId,
        CassieSendingCassieMessage,
        ItemCackling,
        ItemChangingAmmo,
        ItemChangingAttachments,
        ItemChangingMicroHIDPickupState,
        ItemChargingJailbird,
        ItemDisruptorFiring,
        ItemInspectedItem,
        ItemInspectingItem,
        ItemJailbirdChangedWearState,
        ItemJailbirdChangingWearState,
        ItemJailbirdChargeComplete,
        ItemKeycardInteracting,
        ItemPunching,
        ItemReceivingPreference,
        ItemSwinging,
        ItemUsingRadioPickupBattery,
        MapAnnouncingDecontamination,
        MapAnnouncingScpTermination,
        MapChangedIntoGrenade,
        MapChangingIntoGrenade,
        MapDecontaminating,
        MapElevatorSequencesUpdated,
        MapFillingLocker,
        MapGenerated,
        MapGenerating,
        MapGeneratorActivating,
        MapPickupAdded,
        MapPickupDestroyed,
        MapPlacingBulletHole,
        MapPlacingPickupIntoPocketDimension,
        MapScp244Spawning,
        MapSpawningGrenadeEffect,
        MapSpawningItem,
        MapSpawningRoomConnector,
        MapSpawningTeamVehicle,
        MapTurningOffLights,
        PlayerActivatingWorkstation,
        PlayerAimingDownSight,
        PlayerBanned,
        PlayerBanning,
        PlayerCancelledItemUse,
        PlayerCancellingItemUse,
        PlayerChangedEmotion,
        PlayerChangedItem,
        PlayerChangedRatio,
        PlayerChangingDangerState,
        PlayerChangingDisruptorMode,
        PlayerChangingEmotion,
        PlayerChangingGroup,
        PlayerChangingItem,
        PlayerChangingMoveState,
        PlayerChangingNickname,
        PlayerChangingRadioPreset,
        PlayerChangingSpectatedPlayer,
        PlayerClosingGenerator,
        PlayerConsumingItem,
        PlayerDamagingDoor,
        PlayerDamagingShootingTarget,
        PlayerDamagingWindow,
        PlayerDeactivatingWorkstation,
        PlayerDestroying,
        ReservedPlayerDiedEventId,
        PlayerDrinkingCoffee,
        PlayerDroppedAmmo,
        PlayerDroppingAmmo,
        PlayerDroppingItem,
        PlayerDroppingNothing,
        PlayerDryfiringWeapon,
        PlayerEarningAchievement,
        PlayerEnteringEnvironmentalHazard,
        PlayerEnteringKillerCollision,
        ReservedPlayerEscapedEventId,
        PlayerExitingEnvironmentalHazard,
        PlayerExplodingMicroHID,
        PlayerFailingEscapePocketDimension,
        PlayerFlippingCoin,
        PlayerHealed,
        PlayerHealing,
        PlayerHit,
        ReservedPlayerHurtEventId,
        PlayerInteracted,
        PlayerInteractingLocker,
        PlayerInteractingShootingTarget,
        PlayerIntercomSpeaking,
        PlayerIssuingMute,
        PlayerItemAdded,
        PlayerItemRemoved,
        ReservedPlayerJoinedEventId,
        PlayerJumping,
        PlayerKicked,
        PlayerKicking,
        PlayerLanding,
        PlayerMakingNoise,
        PlayerMicroHIDOpeningDoor,
        PlayerOpeningGenerator,
        PlayerPlayingAudioLog,
        PlayerPreAuthenticating,
        PlayerReceivingEffect,
        PlayerReceivingGunSound,
        PlayerReceivingVoiceMessage,
        PlayerReloadedWeapon,
        PlayerReloadingWeapon,
        PlayerRemovedHandcuffs,
        PlayerRemovingHandcuffs,
        PlayerReservedSlot,
        PlayerRevokingMute,
        PlayerRoomChanged,
        PlayerRotatingRevolver,
        PlayerSavingByAntiScp207,
        PlayerScp1576TransmissionEnded,
        PlayerSearchingPickup,
        PlayerSendingAdminChatMessage,
        PlayerSendingGunSound,
        PlayerSendingValidCommand,
        PlayerSentValidCommand,
        ReservedPlayerShotEventId,
        PlayerSpawned,
        PlayerSpawnedRagdoll,
        PlayerSpawning,
        PlayerSpawningRagdoll,
        PlayerStayingOnEnvironmentalHazard,
        PlayerStoppingGenerator,
        PlayerThrowingRequest,
        PlayerTogglingFlashlight,
        PlayerTogglingNoClip,
        PlayerTogglingOverwatch,
        PlayerTogglingRadio,
        PlayerTogglingWeaponFlashlight,
        PlayerTransmitting,
        PlayerTriggeringTesla,
        PlayerUnloadedWeapon,
        PlayerUnloadingWeapon,
        PlayerUnlockingGenerator,
        PlayerUsingItem,
        PlayerUsingItemCompleted,
        PlayerUsingMicroHIDEnergy,
        PlayerUsingRadioBattery,
        PlayerVoiceChatting,
        PlayerZoneChanged,
        Scp049ActivatingSense,
        Scp049Attacking,
        Scp049FinishingRecall,
        Scp049FinishingSense,
        Scp049SendingCall,
        Scp049StartingRecall,
        Scp0492ConsumedCorpse,
        Scp0492ConsumingCorpse,
        Scp0492TriggeringBloodlust,
        Scp079ChangingCamera,
        Scp079ChangingSpeakerStatus,
        Scp079ElevatorTeleporting,
        Scp079GainingExperience,
        Scp079GainingLevel,
        Scp079InteractingTesla,
        Scp079LockingDown,
        Scp079LosingSignal,
        Scp079LostSignal,
        Scp079Pinging,
        Scp079Recontained,
        Scp079Recontaining,
        Scp079RoomBlackout,
        Scp079TriggeringDoor,
        Scp079ZoneBlackout,
        Scp096AddingTarget,
        Scp096CalmingDown,
        Scp096Charging,
        Scp096Enraging,
        Scp096RemovingTarget,
        Scp096StartPryingGate,
        Scp096TryingNotToCry,
        Scp106Attacking,
        Scp106ExitStalking,
        Scp106Stalking,
        Scp106Teleporting,
        Scp127GainedExperience,
        Scp127GainingExperience,
        Scp127Talked,
        Scp127Talking,
        Scp1344ChangedStatus,
        Scp1344ChangingStatus,
        Scp1344Deactivated,
        Scp1344Deactivating,
        Scp1344TryingDeactivating,
        Scp1507AttackingDoor,
        Scp1507Screaming,
        Scp1507SpawningFlamingos,
        Scp1507UsingTape,
        Scp1509Resurrecting,
        Scp1509TriggeringAttack,
        Scp173AddingObserver,
        Scp173BeingObserved,
        Scp173Blinking,
        Scp173BlinkingRequest,
        Scp173PlacingTantrum,
        Scp173RemovedObserver,
        Scp173UsingBreakneckSpeeds,
        Scp244DamagingScp244,
        Scp244OpeningScp244,
        Scp244UsingScp244,
        Scp2536FindingPosition,
        Scp2536FoundPosition,
        Scp2536GrantingGift,
        Scp2536OpeningGift,
        Scp3114Dancing,
        Scp3114Disguised,
        Scp3114Disguising,
        Scp3114Revealed,
        Scp3114Revealing,
        Scp3114Slapped,
        Scp3114Strangling,
        Scp3114TryUseBody,
        Scp3114VoiceLines,
        Scp330DroppingScp330,
        Scp330EatenScp330,
        Scp330EatingScp330,
        Scp330InteractingScp330,
        Scp559Interacting,
        Scp559Spawning,
        Scp914Activating,
        Scp914ChangingKnobSetting,
        Scp914UpgradedInventoryItem,
        Scp914UpgradedPickup,
        Scp914UpgradingInventoryItem,
        Scp914UpgradingPickup,
        Scp914UpgradingPlayer,
        Scp939ChangingFocus,
        Scp939Clawed,
        Scp939Lunging,
        Scp939PlacedAmnesticCloud,
        Scp939PlacingAmnesticCloud,
        Scp939PlacingMimicPoint,
        Scp939PlayingFootstep,
        Scp939PlayingSound,
        Scp939PlayingVoice,
        Scp939SavingVoice,
        Scp939UpdatedCloudState,
        Scp939ValidatingVisibility,
        ServerAddingUnitName,
        ServerAllPlayersSpawned,
        ServerChoosingStartTeamQueue,
        ServerCompletingObjective,
        ServerEndingRound,
        ServerLocalReporting,
        ServerReloadedConfigs,
        ServerReloadedGameplay,
        ServerReloadedPermissions,
        ServerReloadedPlugins,
        ServerReloadedRA,
        ServerReloadedTranslations,
        ServerReportingCheater,
        ServerRespawnedTeam,
        ServerRespawningTeam,
        ServerSelectingRespawnTeam,
        ServerUnbanned,
        ServerUnbanning,
        ServerWaitingForPlayers,
        WarheadChangingLeverStatus,
        WarheadDeadmanSwitchInitiating,
        WarheadDetonated,
        WarheadDetonating,
        WarheadStarting,
        WarheadStopping,
        PlayerActivatedGenerator,
        PlayerActivatedWarheadPanel,
        PlayerCalledElevator,
        PlayerUsedElevator,
        PlayerPressedEmergencyDoorButton,
        PlayerHandcuffed,
        PlayerSentToPocketDimension,
        PlayerEscapedPocketDimension,
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
        bool DontRender = true;
        Color IconColor = WHITE;
        bool Handled = false;
        Damage::Type DmgType = Damage::Type::Unknown;
        int Id = 0;
    };
}