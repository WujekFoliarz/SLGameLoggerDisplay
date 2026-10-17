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
#include "EventConditions/NtfWave.hpp"
#include "EventConditions/NtfMiniWave.hpp"
#include "EventConditions/CIWave.hpp"
#include "EventConditions/CIMiniWave.hpp"
#include "EventConditions/BallThrown.hpp"
#include "EventConditions/HitByBall.hpp"
#include "EventConditions/FlashGrenadeThrown.hpp"
#include "EventConditions/FlashGrenadeExploded.hpp"
#include "EventConditions/DroppedItem.hpp"
#include "EventConditions/PlayerJoined.hpp"
#include "EventConditions/PlayerLeft.hpp"
#include "EventConditions/PlayerHurt.hpp"
#include "EventConditions/PlayerShot.hpp"
#include "EventConditions/ItemUsed.hpp"
#include "EventConditions/PlayerActivatedGenerator.hpp"
#include "EventConditions/PlayerActivatedWarheadPanel.hpp"
#include "EventConditions/PlayerCalledElevator.hpp"
#include "EventConditions/PlayerUsedElevator.hpp"
#include "EventConditions/PlayerPressedEmergencyDoorButton.hpp"
#include "EventConditions/PlayerHandcuffed.hpp"
#include "EventConditions/PlayerSentToPocketDimension.hpp"
#include "EventConditions/PlayerEscapedPocketDimension.hpp"
#include "EventConditions/CassieSendingCassieMessage.hpp"
#include "EventConditions/ItemDisruptorFiring.hpp"
#include "EventConditions/ItemJailbirdChargeComplete.hpp"
#include "EventConditions/ItemPunching.hpp"
#include "EventConditions/MapAnnouncingDecontamination.hpp"
#include "EventConditions/MapAnnouncingScpTermination.hpp"
#include "EventConditions/MapDecontaminating.hpp"
#include "EventConditions/MapGeneratorActivating.hpp"
#include "EventConditions/MapPlacingBulletHole.hpp"
#include "EventConditions/PlayerBanned.hpp"
#include "EventConditions/PlayerExplodingMicroHID.hpp"
#include "EventConditions/PlayerHit.hpp"
#include "EventConditions/PlayerIntercomSpeaking.hpp"
#include "EventConditions/PlayerKicked.hpp"
#include "EventConditions/PlayerKicking.hpp"
#include "EventConditions/PlayerTriggeringTesla.hpp"
#include "EventConditions/Scp049Attacking.hpp"
#include "EventConditions/Scp049FinishingRecall.hpp"
#include "EventConditions/Scp079Recontained.hpp"
#include "EventConditions/Scp079Recontaining.hpp"
#include "EventConditions/Scp079RoomBlackout.hpp"
#include "EventConditions/Scp079ZoneBlackout.hpp"
#include "EventConditions/Scp096AddingTarget.hpp"
#include "EventConditions/Scp096Charging.hpp"
#include "EventConditions/Scp096Enraging.hpp"
#include "EventConditions/Scp106Attacking.hpp"
#include "EventConditions/Scp106Teleporting.hpp"
#include "EventConditions/Scp173PlacingTantrum.hpp"
#include "EventConditions/Scp244DamagingScp244.hpp"
#include "EventConditions/Scp244OpeningScp244.hpp"
#include "EventConditions/Scp2536GrantingGift.hpp"
#include "EventConditions/Scp3114Strangling.hpp"
#include "EventConditions/Scp914UpgradingPlayer.hpp"
#include "EventConditions/Scp939Clawed.hpp"
#include "EventConditions/Scp939Lunging.hpp"
#include "EventConditions/Scp939PlacingAmnesticCloud.hpp"
#include "EventConditions/ServerCompletingObjective.hpp"
#include "EventConditions/ServerEndingRound.hpp"
#include "EventConditions/ServerReportingCheater.hpp"
#include "EventConditions/ServerRespawnedTeam.hpp"
#include "EventConditions/WarheadDeadmanSwitchInitiating.hpp"
#include "EventConditions/WarheadDetonated.hpp"
#include "EventConditions/WarheadDetonating.hpp"
#include "EventConditions/WarheadStarting.hpp"
#include "EventConditions/WarheadStopping.hpp"

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
                 return result;
             }},
            {Events::EventEnum::PlayerPosition, &EventConditions::PlayerPosition::GetResult},
            {Events::EventEnum::PlayerDied, &EventConditions::PlayerDied::GetResult},
            {Events::EventEnum::NtfWave, &EventConditions::NtfWave::GetResult},
            {Events::EventEnum::NtfMiniWave, &EventConditions::NtfMiniWave::GetResult},
            {Events::EventEnum::CIWave, &EventConditions::CIWave::GetResult},
            {Events::EventEnum::CIMiniWave, &EventConditions::CIMiniWave::GetResult},
            {Events::EventEnum::BallThrown, &EventConditions::BallThrown::GetResult},
            {Events::EventEnum::HitByBall, &EventConditions::HitByBall::GetResult},
            {Events::EventEnum::GrenadeThrown, &EventConditions::GrenadeThrown::GetResult},
            {Events::EventEnum::GrenadeExploded, &EventConditions::GrenadeExploded::GetResult},
            {Events::EventEnum::FlashGrenadeThrown, &EventConditions::FlashGrenadeThrown::GetResult},
            {Events::EventEnum::FlashGrenadeExploded, &EventConditions::FlashGrenadeExploded::GetResult},
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
            {Events::EventEnum::DroppedItem, &EventConditions::DroppedItem::GetResult},
            {Events::EventEnum::PlayerJoined, &EventConditions::PlayerJoined::GetResult},
            {Events::EventEnum::PlayerLeft, &EventConditions::PlayerLeft::GetResult},
            // Archived event handler: PlayerChangedRoles -> PlayerChangedRoles
            {Events::EventEnum::PlayerHurt, &EventConditions::PlayerHurt::GetResult},
            {Events::EventEnum::PlayerShot, &EventConditions::PlayerShot::GetResult},
            {Events::EventEnum::ItemUsed, &EventConditions::ItemUsed::GetResult},
            {Events::EventEnum::PlayerActivatedGenerator, &EventConditions::PlayerActivatedGenerator::GetResult},
            {Events::EventEnum::PlayerActivatedWarheadPanel, &EventConditions::PlayerActivatedWarheadPanel::GetResult},
            {Events::EventEnum::PlayerCalledElevator, &EventConditions::PlayerCalledElevator::GetResult},
            {Events::EventEnum::PlayerUsedElevator, &EventConditions::PlayerUsedElevator::GetResult},
            {Events::EventEnum::PlayerPressedEmergencyDoorButton, &EventConditions::PlayerPressedEmergencyDoorButton::GetResult},
            {Events::EventEnum::PlayerHandcuffed, &EventConditions::PlayerHandcuffed::GetResult},
            {Events::EventEnum::PlayerSentToPocketDimension, &EventConditions::PlayerSentToPocketDimension::GetResult},
            {Events::EventEnum::PlayerEscapedPocketDimension, &EventConditions::PlayerEscapedPocketDimension::GetResult},
            {Events::EventEnum::CassieSendingCassieMessage, &EventConditions::CassieSendingCassieMessage::GetResult},
            // Archived event handler: ItemCackling -> ItemCackling
            // Archived event handler: ItemChangingAmmo -> ItemChangingAmmo
            // Archived event handler: ItemChangingAttachments -> ItemChangingAttachments
            // Archived event handler: ItemChangingMicroHIDPickupState -> ItemChangingMicroHIDPickupState
            // Archived event handler: ItemChargingJailbird -> ItemChargingJailbird
            {Events::EventEnum::ItemDisruptorFiring, &EventConditions::ItemDisruptorFiring::GetResult},
            // Archived event handler: ItemInspectedItem -> ItemInspectedItem
            // Archived event handler: ItemInspectingItem -> ItemInspectingItem
            // Archived event handler: ItemJailbirdChangedWearState -> ItemJailbirdChangedWearState
            // Archived event handler: ItemJailbirdChangingWearState -> ItemJailbirdChangingWearState
            {Events::EventEnum::ItemJailbirdChargeComplete, &EventConditions::ItemJailbirdChargeComplete::GetResult},
            // Archived event handler: ItemKeycardInteracting -> ItemKeycardInteracting
            {Events::EventEnum::ItemPunching, &EventConditions::ItemPunching::GetResult},
            // Archived event handler: ItemReceivingPreference -> ItemReceivingPreference
            // Archived event handler: ItemSwinging -> ItemSwinging
            // Archived event handler: ItemUsingRadioPickupBattery -> ItemUsingRadioPickupBattery
            {Events::EventEnum::MapAnnouncingDecontamination, &EventConditions::MapAnnouncingDecontamination::GetResult},
            {Events::EventEnum::MapAnnouncingScpTermination, &EventConditions::MapAnnouncingScpTermination::GetResult},
            // Archived event handler: MapChangedIntoGrenade -> MapChangedIntoGrenade
            // Archived event handler: MapChangingIntoGrenade -> MapChangingIntoGrenade
            {Events::EventEnum::MapDecontaminating, &EventConditions::MapDecontaminating::GetResult},
            // Archived event handler: MapElevatorSequencesUpdated -> MapElevatorSequencesUpdated
            // Archived event handler: MapFillingLocker -> MapFillingLocker
            // Archived event handler: MapGenerated -> MapGenerated
            // Archived event handler: MapGenerating -> MapGenerating
            {Events::EventEnum::MapGeneratorActivating, &EventConditions::MapGeneratorActivating::GetResult},
            // Archived event handler: MapPickupAdded -> MapPickupAdded
            // Archived event handler: MapPickupDestroyed -> MapPickupDestroyed
            {Events::EventEnum::MapPlacingBulletHole, &EventConditions::MapPlacingBulletHole::GetResult},
            // Archived event handler: MapPlacingPickupIntoPocketDimension -> MapPlacingPickupIntoPocketDimension
            // Archived event handler: MapScp244Spawning -> MapScp244Spawning
            // Archived event handler: MapSpawningGrenadeEffect -> MapSpawningGrenadeEffect
            // Archived event handler: MapSpawningItem -> MapSpawningItem
            // Archived event handler: MapSpawningRoomConnector -> MapSpawningRoomConnector
            // Archived event handler: MapSpawningTeamVehicle -> MapSpawningTeamVehicle
            // Archived event handler: MapTurningOffLights -> MapTurningOffLights
            // Archived event handler: PlayerActivatingWorkstation -> PlayerActivatingWorkstation
            // Archived event handler: PlayerAimingDownSight -> PlayerAimingDownSight
            {Events::EventEnum::PlayerBanned, &EventConditions::PlayerBanned::GetResult},
            // Archived event handler: PlayerBanning -> PlayerBanning
            // Archived event handler: PlayerCancelledItemUse -> PlayerCancelledItemUse
            // Archived event handler: PlayerCancellingItemUse -> PlayerCancellingItemUse
            // Archived event handler: PlayerChangedEmotion -> PlayerChangedEmotion
            // Archived event handler: PlayerChangedItem -> PlayerChangedItem
            // Archived event handler: PlayerChangedRatio -> PlayerChangedRatio
            // Archived event handler: PlayerChangingDangerState -> PlayerChangingDangerState
            // Archived event handler: PlayerChangingDisruptorMode -> PlayerChangingDisruptorMode
            // Archived event handler: PlayerChangingEmotion -> PlayerChangingEmotion
            // Archived event handler: PlayerChangingGroup -> PlayerChangingGroup
            // Archived event handler: PlayerChangingItem -> PlayerChangingItem
            // Archived event handler: PlayerChangingMoveState -> PlayerChangingMoveState
            // Archived event handler: PlayerChangingNickname -> PlayerChangingNickname
            // Archived event handler: PlayerChangingRadioPreset -> PlayerChangingRadioPreset
            // Archived event handler: PlayerChangingSpectatedPlayer -> PlayerChangingSpectatedPlayer
            // Archived event handler: PlayerClosingGenerator -> PlayerClosingGenerator
            // Archived event handler: PlayerConsumingItem -> PlayerConsumingItem
            // Archived event handler: PlayerDamagingDoor -> PlayerDamagingDoor
            // Archived event handler: PlayerDamagingShootingTarget -> PlayerDamagingShootingTarget
            // Archived event handler: PlayerDamagingWindow -> PlayerDamagingWindow
            // Archived event handler: PlayerDeactivatingWorkstation -> PlayerDeactivatingWorkstation
            // Archived event handler: PlayerDestroying -> PlayerDestroying
            // Archived event handler: PlayerDrinkingCoffee -> PlayerDrinkingCoffee
            // Archived event handler: PlayerDroppedAmmo -> PlayerDroppedAmmo
            // Archived event handler: PlayerDroppingAmmo -> PlayerDroppingAmmo
            // Archived event handler: PlayerDroppingItem -> PlayerDroppingItem
            // Archived event handler: PlayerDroppingNothing -> PlayerDroppingNothing
            // Archived event handler: PlayerDryfiringWeapon -> PlayerDryfiringWeapon
            // Archived event handler: PlayerEarningAchievement -> PlayerEarningAchievement
            // Archived event handler: PlayerEnteringEnvironmentalHazard -> PlayerEnteringEnvironmentalHazard
            // Archived event handler: PlayerEnteringKillerCollision -> PlayerEnteringKillerCollision
            // Archived event handler: PlayerExitingEnvironmentalHazard -> PlayerExitingEnvironmentalHazard
            {Events::EventEnum::PlayerExplodingMicroHID, &EventConditions::PlayerExplodingMicroHID::GetResult},
            // Archived event handler: PlayerFailingEscapePocketDimension -> PlayerFailingEscapePocketDimension
            // Archived event handler: PlayerFlippingCoin -> PlayerFlippingCoin
            // Archived event handler: PlayerHealed -> PlayerHealed
            // Archived event handler: PlayerHealing -> PlayerHealing
            {Events::EventEnum::PlayerHit, &EventConditions::PlayerHit::GetResult},
            // Archived event handler: PlayerInteracted -> PlayerInteracted
            // Archived event handler: PlayerInteractingLocker -> PlayerInteractingLocker
            // Archived event handler: PlayerInteractingShootingTarget -> PlayerInteractingShootingTarget
            {Events::EventEnum::PlayerIntercomSpeaking, &EventConditions::PlayerIntercomSpeaking::GetResult},
            // Archived event handler: PlayerIssuingMute -> PlayerIssuingMute
            // Archived event handler: PlayerItemAdded -> PlayerItemAdded
            // Archived event handler: PlayerItemRemoved -> PlayerItemRemoved
            // Archived event handler: PlayerJumping -> PlayerJumping
            {Events::EventEnum::PlayerKicked, &EventConditions::PlayerKicked::GetResult},
            {Events::EventEnum::PlayerKicking, &EventConditions::PlayerKicking::GetResult},
            // Archived event handler: PlayerLanding -> PlayerLanding
            // Archived event handler: PlayerMakingNoise -> PlayerMakingNoise
            // Archived event handler: PlayerMicroHIDOpeningDoor -> PlayerMicroHIDOpeningDoor
            // Archived event handler: PlayerOpeningGenerator -> PlayerOpeningGenerator
            // Archived event handler: PlayerPlayingAudioLog -> PlayerPlayingAudioLog
            // Archived event handler: PlayerPreAuthenticating -> PlayerPreAuthenticating
            // Archived event handler: PlayerReceivingEffect -> PlayerReceivingEffect
            // Archived event handler: PlayerReceivingGunSound -> PlayerReceivingGunSound
            // Archived event handler: PlayerReceivingVoiceMessage -> PlayerReceivingVoiceMessage
            // Archived event handler: PlayerReloadedWeapon -> PlayerReloadedWeapon
            // Archived event handler: PlayerReloadingWeapon -> PlayerReloadingWeapon
            // Archived event handler: PlayerRemovedHandcuffs -> PlayerRemovedHandcuffs
            // Archived event handler: PlayerRemovingHandcuffs -> PlayerRemovingHandcuffs
            // Archived event handler: PlayerReservedSlot -> PlayerReservedSlot
            // Archived event handler: PlayerRevokingMute -> PlayerRevokingMute
            // Archived event handler: PlayerRoomChanged -> PlayerRoomChanged
            // Archived event handler: PlayerRotatingRevolver -> PlayerRotatingRevolver
            // Archived event handler: PlayerSavingByAntiScp207 -> PlayerSavingByAntiScp207
            // Archived event handler: PlayerScp1576TransmissionEnded -> PlayerScp1576TransmissionEnded
            // Archived event handler: PlayerSearchingPickup -> PlayerSearchingPickup
            // Archived event handler: PlayerSendingAdminChatMessage -> PlayerSendingAdminChatMessage
            // Archived event handler: PlayerSendingGunSound -> PlayerSendingGunSound
            // Archived event handler: PlayerSendingValidCommand -> PlayerSendingValidCommand
            // Archived event handler: PlayerSentValidCommand -> PlayerSentValidCommand
            // Archived event handler: PlayerSpawned -> PlayerSpawned
            // Archived event handler: PlayerSpawnedRagdoll -> PlayerSpawnedRagdoll
            // Archived event handler: PlayerSpawning -> PlayerSpawning
            // Archived event handler: PlayerSpawningRagdoll -> PlayerSpawningRagdoll
            // Archived event handler: PlayerStayingOnEnvironmentalHazard -> PlayerStayingOnEnvironmentalHazard
            // Archived event handler: PlayerStoppingGenerator -> PlayerStoppingGenerator
            // Archived event handler: PlayerThrowingRequest -> PlayerThrowingRequest
            // Archived event handler: PlayerTogglingFlashlight -> PlayerTogglingFlashlight
            // Archived event handler: PlayerTogglingNoClip -> PlayerTogglingNoClip
            // Archived event handler: PlayerTogglingOverwatch -> PlayerTogglingOverwatch
            // Archived event handler: PlayerTogglingRadio -> PlayerTogglingRadio
            // Archived event handler: PlayerTogglingWeaponFlashlight -> PlayerTogglingWeaponFlashlight
            // Archived event handler: PlayerTransmitting -> PlayerTransmitting
            {Events::EventEnum::PlayerTriggeringTesla, &EventConditions::PlayerTriggeringTesla::GetResult},
            // Archived event handler: PlayerUnloadedWeapon -> PlayerUnloadedWeapon
            // Archived event handler: PlayerUnloadingWeapon -> PlayerUnloadingWeapon
            // Archived event handler: PlayerUnlockingGenerator -> PlayerUnlockingGenerator
            // Archived event handler: PlayerUsingItem -> PlayerUsingItem
            // Archived event handler: PlayerUsingItemCompleted -> PlayerUsingItemCompleted
            // Archived event handler: PlayerUsingMicroHIDEnergy -> PlayerUsingMicroHIDEnergy
            // Archived event handler: PlayerUsingRadioBattery -> PlayerUsingRadioBattery
            // Archived event handler: PlayerVoiceChatting -> PlayerVoiceChatting
            // Archived event handler: PlayerZoneChanged -> PlayerZoneChanged
            // Archived event handler: Scp049ActivatingSense -> Scp049ActivatingSense
            {Events::EventEnum::Scp049Attacking, &EventConditions::Scp049Attacking::GetResult},
            {Events::EventEnum::Scp049FinishingRecall, &EventConditions::Scp049FinishingRecall::GetResult},
            // Archived event handler: Scp049FinishingSense -> Scp049FinishingSense
            // Archived event handler: Scp049SendingCall -> Scp049SendingCall
            // Archived event handler: Scp049StartingRecall -> Scp049StartingRecall
            // Archived event handler: Scp0492ConsumedCorpse -> Scp0492ConsumedCorpse
            // Archived event handler: Scp0492ConsumingCorpse -> Scp0492ConsumingCorpse
            // Archived event handler: Scp0492TriggeringBloodlust -> Scp0492TriggeringBloodlust
            // Archived event handler: Scp079ChangingCamera -> Scp079ChangingCamera
            // Archived event handler: Scp079ChangingSpeakerStatus -> Scp079ChangingSpeakerStatus
            // Archived event handler: Scp079ElevatorTeleporting -> Scp079ElevatorTeleporting
            // Archived event handler: Scp079GainingExperience -> Scp079GainingExperience
            // Archived event handler: Scp079GainingLevel -> Scp079GainingLevel
            // Archived event handler: Scp079InteractingTesla -> Scp079InteractingTesla
            // Archived event handler: Scp079LockingDown -> Scp079LockingDown
            // Archived event handler: Scp079LosingSignal -> Scp079LosingSignal
            // Archived event handler: Scp079LostSignal -> Scp079LostSignal
            // Archived event handler: Scp079Pinging -> Scp079Pinging
            {Events::EventEnum::Scp079Recontained, &EventConditions::Scp079Recontained::GetResult},
            {Events::EventEnum::Scp079Recontaining, &EventConditions::Scp079Recontaining::GetResult},
            {Events::EventEnum::Scp079RoomBlackout, &EventConditions::Scp079RoomBlackout::GetResult},
            // Archived event handler: Scp079TriggeringDoor -> Scp079TriggeringDoor
            {Events::EventEnum::Scp079ZoneBlackout, &EventConditions::Scp079ZoneBlackout::GetResult},
            {Events::EventEnum::Scp096AddingTarget, &EventConditions::Scp096AddingTarget::GetResult},
            // Archived event handler: Scp096CalmingDown -> Scp096CalmingDown
            {Events::EventEnum::Scp096Charging, &EventConditions::Scp096Charging::GetResult},
            {Events::EventEnum::Scp096Enraging, &EventConditions::Scp096Enraging::GetResult},
            // Archived event handler: Scp096RemovingTarget -> Scp096RemovingTarget
            // Archived event handler: Scp096StartPryingGate -> Scp096StartPryingGate
            // Archived event handler: Scp096TryingNotToCry -> Scp096TryingNotToCry
            {Events::EventEnum::Scp106Attacking, &EventConditions::Scp106Attacking::GetResult},
            // Archived event handler: Scp106ExitStalking -> Scp106ExitStalking
            // Archived event handler: Scp106Stalking -> Scp106Stalking
            {Events::EventEnum::Scp106Teleporting, &EventConditions::Scp106Teleporting::GetResult},
            // Archived event handler: Scp127GainedExperience -> Scp127GainedExperience
            // Archived event handler: Scp127GainingExperience -> Scp127GainingExperience
            // Archived event handler: Scp127Talked -> Scp127Talked
            // Archived event handler: Scp127Talking -> Scp127Talking
            // Archived event handler: Scp1344ChangedStatus -> Scp1344ChangedStatus
            // Archived event handler: Scp1344ChangingStatus -> Scp1344ChangingStatus
            // Archived event handler: Scp1344Deactivated -> Scp1344Deactivated
            // Archived event handler: Scp1344Deactivating -> Scp1344Deactivating
            // Archived event handler: Scp1344TryingDeactivating -> Scp1344TryingDeactivating
            // Archived event handler: Scp1507AttackingDoor -> Scp1507AttackingDoor
            // Archived event handler: Scp1507Screaming -> Scp1507Screaming
            // Archived event handler: Scp1507SpawningFlamingos -> Scp1507SpawningFlamingos
            // Archived event handler: Scp1507UsingTape -> Scp1507UsingTape
            // Archived event handler: Scp1509Resurrecting -> Scp1509Resurrecting
            // Archived event handler: Scp1509TriggeringAttack -> Scp1509TriggeringAttack
            // Archived event handler: Scp173AddingObserver -> Scp173AddingObserver
            // Archived event handler: Scp173BeingObserved -> Scp173BeingObserved
            // Archived event handler: Scp173Blinking -> Scp173Blinking
            // Archived event handler: Scp173BlinkingRequest -> Scp173BlinkingRequest
            {Events::EventEnum::Scp173PlacingTantrum, &EventConditions::Scp173PlacingTantrum::GetResult},
            // Archived event handler: Scp173RemovedObserver -> Scp173RemovedObserver
            // Archived event handler: Scp173UsingBreakneckSpeeds -> Scp173UsingBreakneckSpeeds
            {Events::EventEnum::Scp244DamagingScp244, &EventConditions::Scp244DamagingScp244::GetResult},
            {Events::EventEnum::Scp244OpeningScp244, &EventConditions::Scp244OpeningScp244::GetResult},
            // Archived event handler: Scp244UsingScp244 -> Scp244UsingScp244
            // Archived event handler: Scp2536FindingPosition -> Scp2536FindingPosition
            // Archived event handler: Scp2536FoundPosition -> Scp2536FoundPosition
            {Events::EventEnum::Scp2536GrantingGift, &EventConditions::Scp2536GrantingGift::GetResult},
            // Archived event handler: Scp2536OpeningGift -> Scp2536OpeningGift
            // Archived event handler: Scp3114Dancing -> Scp3114Dancing
            // Archived event handler: Scp3114Disguised -> Scp3114Disguised
            // Archived event handler: Scp3114Disguising -> Scp3114Disguising
            // Archived event handler: Scp3114Revealed -> Scp3114Revealed
            // Archived event handler: Scp3114Revealing -> Scp3114Revealing
            // Archived event handler: Scp3114Slapped -> Scp3114Slapped
            {Events::EventEnum::Scp3114Strangling, &EventConditions::Scp3114Strangling::GetResult},
            // Archived event handler: Scp3114TryUseBody -> Scp3114TryUseBody
            // Archived event handler: Scp3114VoiceLines -> Scp3114VoiceLines
            // Archived event handler: Scp330DroppingScp330 -> Scp330DroppingScp330
            // Archived event handler: Scp330EatenScp330 -> Scp330EatenScp330
            // Archived event handler: Scp330EatingScp330 -> Scp330EatingScp330
            // Archived event handler: Scp330InteractingScp330 -> Scp330InteractingScp330
            // Archived event handler: Scp559Interacting -> Scp559Interacting
            // Archived event handler: Scp559Spawning -> Scp559Spawning
            // Archived event handler: Scp914Activating -> Scp914Activating
            // Archived event handler: Scp914ChangingKnobSetting -> Scp914ChangingKnobSetting
            // Archived event handler: Scp914UpgradedInventoryItem -> Scp914UpgradedInventoryItem
            // Archived event handler: Scp914UpgradedPickup -> Scp914UpgradedPickup
            // Archived event handler: Scp914UpgradingInventoryItem -> Scp914UpgradingInventoryItem
            // Archived event handler: Scp914UpgradingPickup -> Scp914UpgradingPickup
            {Events::EventEnum::Scp914UpgradingPlayer, &EventConditions::Scp914UpgradingPlayer::GetResult},
            // Archived event handler: Scp939ChangingFocus -> Scp939ChangingFocus
            {Events::EventEnum::Scp939Clawed, &EventConditions::Scp939Clawed::GetResult},
            {Events::EventEnum::Scp939Lunging, &EventConditions::Scp939Lunging::GetResult},
            // Archived event handler: Scp939PlacedAmnesticCloud -> Scp939PlacedAmnesticCloud
            {Events::EventEnum::Scp939PlacingAmnesticCloud, &EventConditions::Scp939PlacingAmnesticCloud::GetResult},
            // Archived event handler: Scp939PlacingMimicPoint -> Scp939PlacingMimicPoint
            // Archived event handler: Scp939PlayingFootstep -> Scp939PlayingFootstep
            // Archived event handler: Scp939PlayingSound -> Scp939PlayingSound
            // Archived event handler: Scp939PlayingVoice -> Scp939PlayingVoice
            // Archived event handler: Scp939SavingVoice -> Scp939SavingVoice
            // Archived event handler: Scp939UpdatedCloudState -> Scp939UpdatedCloudState
            // Archived event handler: Scp939ValidatingVisibility -> Scp939ValidatingVisibility
            // Archived event handler: ServerAddingUnitName -> ServerAddingUnitName
            // Archived event handler: ServerAllPlayersSpawned -> ServerAllPlayersSpawned
            // Archived event handler: ServerChoosingStartTeamQueue -> ServerChoosingStartTeamQueue
            {Events::EventEnum::ServerCompletingObjective, &EventConditions::ServerCompletingObjective::GetResult},
            {Events::EventEnum::ServerEndingRound, &EventConditions::ServerEndingRound::GetResult},
            // Archived event handler: ServerLocalReporting -> ServerLocalReporting
            // Archived event handler: ServerReloadedConfigs -> ServerReloadedConfigs
            // Archived event handler: ServerReloadedGameplay -> ServerReloadedGameplay
            // Archived event handler: ServerReloadedPermissions -> ServerReloadedPermissions
            // Archived event handler: ServerReloadedPlugins -> ServerReloadedPlugins
            // Archived event handler: ServerReloadedRA -> ServerReloadedRA
            // Archived event handler: ServerReloadedTranslations -> ServerReloadedTranslations
            {Events::EventEnum::ServerReportingCheater, &EventConditions::ServerReportingCheater::GetResult},
            {Events::EventEnum::ServerRespawnedTeam, &EventConditions::ServerRespawnedTeam::GetResult},
            // Archived event handler: ServerRespawningTeam -> ServerRespawningTeam
            // Archived event handler: ServerSelectingRespawnTeam -> ServerSelectingRespawnTeam
            // Archived event handler: ServerUnbanned -> ServerUnbanned
            // Archived event handler: ServerUnbanning -> ServerUnbanning
            // Archived event handler: ServerWaitingForPlayers -> ServerWaitingForPlayers
            // Archived event handler: WarheadChangingLeverStatus -> WarheadChangingLeverStatus
            {Events::EventEnum::WarheadDeadmanSwitchInitiating, &EventConditions::WarheadDeadmanSwitchInitiating::GetResult},
            {Events::EventEnum::WarheadDetonated, &EventConditions::WarheadDetonated::GetResult},
            {Events::EventEnum::WarheadDetonating, &EventConditions::WarheadDetonating::GetResult},
            {Events::EventEnum::WarheadStarting, &EventConditions::WarheadStarting::GetResult},
            {Events::EventEnum::WarheadStopping, &EventConditions::WarheadStopping::GetResult},
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