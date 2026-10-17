#pragma once

#include <vector>
#include <unordered_map>
#include <raylib.h>
#include "Events.hpp"
#include "PlayerData.hpp"
#include "AnnounceLog.hpp"

#include "Packets/PacketResolver.hpp"

namespace Replay
{
    struct RoomData
    {
        std::string Name = "";
        Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
        Quaternion Rotation = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    };

    template <typename T>
    class DataHistory
    {
    public:
        void Save(int index, int tick, const T &data)
        {
            m_Map[index][tick] = data;
        }

        const T *Get(int index, int tick) const
        {
            auto historyIt = m_Map.find(index);
            if (historyIt == m_Map.end())
                return nullptr;

            auto dataIt = historyIt->second.find(tick);
            if (dataIt == historyIt->second.end())
                return nullptr;

            return &dataIt->second;
        }

    private:
        std::unordered_map<int, std::unordered_map<int, T>> m_Map;
    };

    struct State
    {
        float kWorldToPixels = 13.347f;
        Vector2 LczOffset{0.0f, 0.0f};
        Vector2 HczOffset{0.0f, 0.0f};
        Vector2 EzOffset{0.0f, 0.0f};
        float EzScale = 1.0f;
        std::vector<Events::Point> Points;
        int TickCount = 0;
        float CurrentTick = 0.0f;
        float PreviousTick = 0.0f;
        int CurrentReadTick = 0;
        float PlaySpeed = 1.0f;
        float TickRate = 60.0f;
        size_t VisiblePoints = 0;
        Vector2 Origin{0.0f, 0.0f};
        float TotalScale = 1.0f;
        float Zoom = 1.0f;
        AnnounceLog::AnnounceLog Log;
        bool Paused = false;
        int HighlightedPlayer = -1;
        bool Exit = false;

        std::vector<RoomData> RoomPositions;
        std::unordered_map<int, Player::Data> Players;
        std::unordered_map<int, std::vector<Packet::Variant>> Data;
        std::unordered_map<int, std::unordered_map<int, Events::RoleTypeId>> PreviousRoleMap;
        std::unordered_map<int, int> LastTimePositionPointPlacedMap;
        DataHistory<Events::RoleTypeId> RoleHistory;
        DataHistory<Player::Data> PlayerHistory;
    };

    void HandlePacket(const Packet::Invalid::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::NewTick::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::Room::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerJoined::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerLeft::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerPosition::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerChangedRoles::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::DoorOpened::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::DoorClosed::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerDied::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::CancelChargingMicroHid::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::ChargingMicroHid::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::FiringMicroHid::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerEscaped::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerEscorted::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::VersionPacket::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::NtfWave::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::NtfMiniWave::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::CIWave::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::CIMiniWave::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::BallThrown::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::HitByBall::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::GrenadeThrown::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::GrenadeExploded::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PickingUpItem::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::DroppedItem::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerHurt::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerShot::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::ItemUsed::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerAction::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::CassieSendingCassieMessage::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: ItemCackling
    // Archived replay handler: ItemChangingAmmo
    // Archived replay handler: ItemChangingAttachments
    // Archived replay handler: ItemChangingMicroHIDPickupState
    // Archived replay handler: ItemChargingJailbird
    void HandlePacket(const Packet::ItemDisruptorFiring::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: ItemInspectedItem
    // Archived replay handler: ItemInspectingItem
    // Archived replay handler: ItemJailbirdChangedWearState
    // Archived replay handler: ItemJailbirdChangingWearState
    void HandlePacket(const Packet::ItemJailbirdChargeComplete::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: ItemKeycardInteracting
    void HandlePacket(const Packet::ItemPunching::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: ItemReceivingPreference
    // Archived replay handler: ItemSwinging
    // Archived replay handler: ItemUsingRadioPickupBattery
    void HandlePacket(const Packet::MapAnnouncingDecontamination::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::MapAnnouncingScpTermination::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: MapChangedIntoGrenade
    // Archived replay handler: MapChangingIntoGrenade
    void HandlePacket(const Packet::MapDecontaminating::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: MapElevatorSequencesUpdated
    // Archived replay handler: MapFillingLocker
    // Archived replay handler: MapGenerated
    // Archived replay handler: MapGenerating
    void HandlePacket(const Packet::MapGeneratorActivating::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: MapPickupAdded
    // Archived replay handler: MapPickupDestroyed
    void HandlePacket(const Packet::MapPlacingBulletHole::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: MapPlacingPickupIntoPocketDimension
    // Archived replay handler: MapScp244Spawning
    // Archived replay handler: MapSpawningGrenadeEffect
    // Archived replay handler: MapSpawningItem
    // Archived replay handler: MapSpawningRoomConnector
    // Archived replay handler: MapSpawningTeamVehicle
    // Archived replay handler: MapTurningOffLights
    // Archived replay handler: PlayerActivatingWorkstation
    // Archived replay handler: PlayerAimingDownSight
    void HandlePacket(const Packet::PlayerBanned::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: PlayerBanning
    // Archived replay handler: PlayerCancelledItemUse
    // Archived replay handler: PlayerCancellingItemUse
    // Archived replay handler: PlayerChangedEmotion
    // Archived replay handler: PlayerChangedItem
    // Archived replay handler: PlayerChangedRatio
    // Archived replay handler: PlayerChangingDangerState
    // Archived replay handler: PlayerChangingDisruptorMode
    // Archived replay handler: PlayerChangingEmotion
    // Archived replay handler: PlayerChangingGroup
    // Archived replay handler: PlayerChangingItem
    // Archived replay handler: PlayerChangingMoveState
    // Archived replay handler: PlayerChangingNickname
    // Archived replay handler: PlayerChangingRadioPreset
    // Archived replay handler: PlayerChangingSpectatedPlayer
    // Archived replay handler: PlayerClosingGenerator
    // Archived replay handler: PlayerConsumingItem
    // Archived replay handler: PlayerDamagingDoor
    // Archived replay handler: PlayerDamagingShootingTarget
    // Archived replay handler: PlayerDamagingWindow
    // Archived replay handler: PlayerDeactivatingWorkstation
    // Archived replay handler: PlayerDestroying
    // Archived replay handler: PlayerDrinkingCoffee
    // Archived replay handler: PlayerDroppedAmmo
    // Archived replay handler: PlayerDroppingAmmo
    // Archived replay handler: PlayerDroppingItem
    // Archived replay handler: PlayerDroppingNothing
    // Archived replay handler: PlayerDryfiringWeapon
    // Archived replay handler: PlayerEarningAchievement
    // Archived replay handler: PlayerEnteringEnvironmentalHazard
    // Archived replay handler: PlayerEnteringKillerCollision
    // Archived replay handler: PlayerExitingEnvironmentalHazard
    void HandlePacket(const Packet::PlayerExplodingMicroHID::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: PlayerFailingEscapePocketDimension
    // Archived replay handler: PlayerFlippingCoin
    // Archived replay handler: PlayerHealed
    // Archived replay handler: PlayerHealing
    void HandlePacket(const Packet::PlayerHit::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: PlayerInteracted
    // Archived replay handler: PlayerInteractingLocker
    // Archived replay handler: PlayerInteractingShootingTarget
    void HandlePacket(const Packet::PlayerIntercomSpeaking::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: PlayerIssuingMute
    // Archived replay handler: PlayerItemAdded
    // Archived replay handler: PlayerItemRemoved
    // Archived replay handler: PlayerJumping
    void HandlePacket(const Packet::PlayerKicked::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::PlayerKicking::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: PlayerLanding
    // Archived replay handler: PlayerMakingNoise
    // Archived replay handler: PlayerMicroHIDOpeningDoor
    // Archived replay handler: PlayerOpeningGenerator
    // Archived replay handler: PlayerPlayingAudioLog
    // Archived replay handler: PlayerPreAuthenticating
    // Archived replay handler: PlayerReceivingEffect
    // Archived replay handler: PlayerReceivingGunSound
    // Archived replay handler: PlayerReceivingVoiceMessage
    // Archived replay handler: PlayerReloadedWeapon
    // Archived replay handler: PlayerReloadingWeapon
    // Archived replay handler: PlayerRemovedHandcuffs
    // Archived replay handler: PlayerRemovingHandcuffs
    // Archived replay handler: PlayerReservedSlot
    // Archived replay handler: PlayerRevokingMute
    // Archived replay handler: PlayerRoomChanged
    // Archived replay handler: PlayerRotatingRevolver
    // Archived replay handler: PlayerSavingByAntiScp207
    // Archived replay handler: PlayerScp1576TransmissionEnded
    // Archived replay handler: PlayerSearchingPickup
    // Archived replay handler: PlayerSendingAdminChatMessage
    // Archived replay handler: PlayerSendingGunSound
    // Archived replay handler: PlayerSendingValidCommand
    // Archived replay handler: PlayerSentValidCommand
    // Archived replay handler: PlayerSpawned
    // Archived replay handler: PlayerSpawnedRagdoll
    // Archived replay handler: PlayerSpawning
    // Archived replay handler: PlayerSpawningRagdoll
    // Archived replay handler: PlayerStayingOnEnvironmentalHazard
    // Archived replay handler: PlayerStoppingGenerator
    // Archived replay handler: PlayerThrowingRequest
    // Archived replay handler: PlayerTogglingFlashlight
    // Archived replay handler: PlayerTogglingNoClip
    // Archived replay handler: PlayerTogglingOverwatch
    // Archived replay handler: PlayerTogglingRadio
    // Archived replay handler: PlayerTogglingWeaponFlashlight
    // Archived replay handler: PlayerTransmitting
    void HandlePacket(const Packet::PlayerTriggeringTesla::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: PlayerUnloadedWeapon
    // Archived replay handler: PlayerUnloadingWeapon
    // Archived replay handler: PlayerUnlockingGenerator
    // Archived replay handler: PlayerUsingItem
    // Archived replay handler: PlayerUsingItemCompleted
    // Archived replay handler: PlayerUsingMicroHIDEnergy
    // Archived replay handler: PlayerUsingRadioBattery
    // Archived replay handler: PlayerVoiceChatting
    // Archived replay handler: PlayerZoneChanged
    // Archived replay handler: Scp049ActivatingSense
    void HandlePacket(const Packet::Scp049Attacking::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::Scp049FinishingRecall::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp049FinishingSense
    // Archived replay handler: Scp049SendingCall
    // Archived replay handler: Scp049StartingRecall
    // Archived replay handler: Scp0492ConsumedCorpse
    // Archived replay handler: Scp0492ConsumingCorpse
    // Archived replay handler: Scp0492TriggeringBloodlust
    // Archived replay handler: Scp079ChangingCamera
    // Archived replay handler: Scp079ChangingSpeakerStatus
    // Archived replay handler: Scp079ElevatorTeleporting
    // Archived replay handler: Scp079GainingExperience
    // Archived replay handler: Scp079GainingLevel
    // Archived replay handler: Scp079InteractingTesla
    // Archived replay handler: Scp079LockingDown
    // Archived replay handler: Scp079LosingSignal
    // Archived replay handler: Scp079LostSignal
    // Archived replay handler: Scp079Pinging
    void HandlePacket(const Packet::Scp079Recontained::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::Scp079Recontaining::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::Scp079RoomBlackout::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp079TriggeringDoor
    void HandlePacket(const Packet::Scp079ZoneBlackout::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::Scp096AddingTarget::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp096CalmingDown
    void HandlePacket(const Packet::Scp096Charging::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::Scp096Enraging::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp096RemovingTarget
    // Archived replay handler: Scp096StartPryingGate
    // Archived replay handler: Scp096TryingNotToCry
    void HandlePacket(const Packet::Scp106Attacking::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp106ExitStalking
    // Archived replay handler: Scp106Stalking
    void HandlePacket(const Packet::Scp106Teleporting::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp127GainedExperience
    // Archived replay handler: Scp127GainingExperience
    // Archived replay handler: Scp127Talked
    // Archived replay handler: Scp127Talking
    // Archived replay handler: Scp1344ChangedStatus
    // Archived replay handler: Scp1344ChangingStatus
    // Archived replay handler: Scp1344Deactivated
    // Archived replay handler: Scp1344Deactivating
    // Archived replay handler: Scp1344TryingDeactivating
    // Archived replay handler: Scp1507AttackingDoor
    // Archived replay handler: Scp1507Screaming
    // Archived replay handler: Scp1507SpawningFlamingos
    // Archived replay handler: Scp1507UsingTape
    // Archived replay handler: Scp1509Resurrecting
    // Archived replay handler: Scp1509TriggeringAttack
    // Archived replay handler: Scp173AddingObserver
    // Archived replay handler: Scp173BeingObserved
    // Archived replay handler: Scp173Blinking
    // Archived replay handler: Scp173BlinkingRequest
    void HandlePacket(const Packet::Scp173PlacingTantrum::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp173RemovedObserver
    // Archived replay handler: Scp173UsingBreakneckSpeeds
    void HandlePacket(const Packet::Scp244DamagingScp244::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::Scp244OpeningScp244::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp244UsingScp244
    // Archived replay handler: Scp2536FindingPosition
    // Archived replay handler: Scp2536FoundPosition
    void HandlePacket(const Packet::Scp2536GrantingGift::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp2536OpeningGift
    // Archived replay handler: Scp3114Dancing
    // Archived replay handler: Scp3114Disguised
    // Archived replay handler: Scp3114Disguising
    // Archived replay handler: Scp3114Revealed
    // Archived replay handler: Scp3114Revealing
    // Archived replay handler: Scp3114Slapped
    void HandlePacket(const Packet::Scp3114Strangling::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp3114TryUseBody
    // Archived replay handler: Scp3114VoiceLines
    // Archived replay handler: Scp330DroppingScp330
    // Archived replay handler: Scp330EatenScp330
    // Archived replay handler: Scp330EatingScp330
    // Archived replay handler: Scp330InteractingScp330
    // Archived replay handler: Scp559Interacting
    // Archived replay handler: Scp559Spawning
    // Archived replay handler: Scp914Activating
    // Archived replay handler: Scp914ChangingKnobSetting
    // Archived replay handler: Scp914UpgradedInventoryItem
    // Archived replay handler: Scp914UpgradedPickup
    // Archived replay handler: Scp914UpgradingInventoryItem
    // Archived replay handler: Scp914UpgradingPickup
    void HandlePacket(const Packet::Scp914UpgradingPlayer::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp939ChangingFocus
    void HandlePacket(const Packet::Scp939Clawed::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::Scp939Lunging::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp939PlacedAmnesticCloud
    void HandlePacket(const Packet::Scp939PlacingAmnesticCloud::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: Scp939PlacingMimicPoint
    // Archived replay handler: Scp939PlayingFootstep
    // Archived replay handler: Scp939PlayingSound
    // Archived replay handler: Scp939PlayingVoice
    // Archived replay handler: Scp939SavingVoice
    // Archived replay handler: Scp939UpdatedCloudState
    // Archived replay handler: Scp939ValidatingVisibility
    // Archived replay handler: ServerAddingUnitName
    // Archived replay handler: ServerAllPlayersSpawned
    // Archived replay handler: ServerChoosingStartTeamQueue
    void HandlePacket(const Packet::ServerCompletingObjective::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::ServerEndingRound::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: ServerLocalReporting
    // Archived replay handler: ServerReloadedConfigs
    // Archived replay handler: ServerReloadedGameplay
    // Archived replay handler: ServerReloadedPermissions
    // Archived replay handler: ServerReloadedPlugins
    // Archived replay handler: ServerReloadedRA
    // Archived replay handler: ServerReloadedTranslations
    void HandlePacket(const Packet::ServerReportingCheater::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::ServerRespawnedTeam::Data &data, State &state, bool playedInReverse);
    // Archived replay handler: ServerRespawningTeam
    // Archived replay handler: ServerSelectingRespawnTeam
    // Archived replay handler: ServerUnbanned
    // Archived replay handler: ServerUnbanning
    // Archived replay handler: ServerWaitingForPlayers
    // Archived replay handler: WarheadChangingLeverStatus
    void HandlePacket(const Packet::WarheadDeadmanSwitchInitiating::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::WarheadDetonated::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::WarheadDetonating::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::WarheadStarting::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::WarheadStopping::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::FlashGrenadeThrown::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::FlashGrenadeExploded::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::SCP268Used::Data &data, State &state, bool playedInReverse);
    void HandlePacket(const Packet::SCP268Expired::Data &data, State &state, bool playedInReverse);
}