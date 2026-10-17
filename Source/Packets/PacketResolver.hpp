#pragma once

#include "../Events.hpp"
#include <variant>
#include <vector>
#include <cstdint>

#include "Invalid.hpp"
#include "NewTick.hpp"
#include "Room.hpp"
#include "PlayerJoined.hpp"
#include "PlayerPosition.hpp"
#include "PlayerChangedRoles.hpp"
#include "PlayerLeft.hpp"
#include "DoorOpened.hpp"
#include "DoorClosed.hpp"
#include "PlayerDied.hpp"
#include "CancelChargingMicroHid.hpp"
#include "ChargingMicroHid.hpp"
#include "FiringMicroHid.hpp"
#include "PlayerEscaped.hpp"
#include "PlayerEscorted.hpp"
#include "VersionPacket.hpp"
#include "NtfWave.hpp"
#include "NtfMiniWave.hpp"
#include "CIWave.hpp"
#include "CIMiniWave.hpp"
#include "BallThrown.hpp"
#include "HitByBall.hpp"
#include "GrenadeThrown.hpp"
#include "GrenadeExploded.hpp"
#include "PickingUpItem.hpp"
#include "DroppedItem.hpp"
#include "PlayerHurt.hpp"
#include "PlayerShot.hpp"
#include "ItemUsed.hpp"
#include "PlayerAction.hpp"
#include "CassieSendingCassieMessage.hpp"
// Archived packet: #include "ItemCackling.hpp"
// Archived packet: #include "ItemChangingAmmo.hpp"
// Archived packet: #include "ItemChangingAttachments.hpp"
// Archived packet: #include "ItemChangingMicroHIDPickupState.hpp"
// Archived packet: #include "ItemChargingJailbird.hpp"
#include "ItemDisruptorFiring.hpp"
// Archived packet: #include "ItemInspectedItem.hpp"
// Archived packet: #include "ItemInspectingItem.hpp"
// Archived packet: #include "ItemJailbirdChangedWearState.hpp"
// Archived packet: #include "ItemJailbirdChangingWearState.hpp"
#include "ItemJailbirdChargeComplete.hpp"
// Archived packet: #include "ItemKeycardInteracting.hpp"
#include "ItemPunching.hpp"
// Archived packet: #include "ItemReceivingPreference.hpp"
// Archived packet: #include "ItemSwinging.hpp"
// Archived packet: #include "ItemUsingRadioPickupBattery.hpp"
#include "MapAnnouncingDecontamination.hpp"
#include "MapAnnouncingScpTermination.hpp"
// Archived packet: #include "MapChangedIntoGrenade.hpp"
// Archived packet: #include "MapChangingIntoGrenade.hpp"
#include "MapDecontaminating.hpp"
// Archived packet: #include "MapElevatorSequencesUpdated.hpp"
// Archived packet: #include "MapFillingLocker.hpp"
// Archived packet: #include "MapGenerated.hpp"
// Archived packet: #include "MapGenerating.hpp"
#include "MapGeneratorActivating.hpp"
// Archived packet: #include "MapPickupAdded.hpp"
// Archived packet: #include "MapPickupDestroyed.hpp"
#include "MapPlacingBulletHole.hpp"
// Archived packet: #include "MapPlacingPickupIntoPocketDimension.hpp"
// Archived packet: #include "MapScp244Spawning.hpp"
// Archived packet: #include "MapSpawningGrenadeEffect.hpp"
// Archived packet: #include "MapSpawningItem.hpp"
// Archived packet: #include "MapSpawningRoomConnector.hpp"
// Archived packet: #include "MapSpawningTeamVehicle.hpp"
// Archived packet: #include "MapTurningOffLights.hpp"
// Archived packet: #include "PlayerActivatingWorkstation.hpp"
// Archived packet: #include "PlayerAimingDownSight.hpp"
#include "PlayerBanned.hpp"
// Archived packet: #include "PlayerBanning.hpp"
// Archived packet: #include "PlayerCancelledItemUse.hpp"
// Archived packet: #include "PlayerCancellingItemUse.hpp"
// Archived packet: #include "PlayerChangedEmotion.hpp"
// Archived packet: #include "PlayerChangedItem.hpp"
// Archived packet: #include "PlayerChangedRatio.hpp"
// Archived packet: #include "PlayerChangingDangerState.hpp"
// Archived packet: #include "PlayerChangingDisruptorMode.hpp"
// Archived packet: #include "PlayerChangingEmotion.hpp"
// Archived packet: #include "PlayerChangingGroup.hpp"
// Archived packet: #include "PlayerChangingItem.hpp"
// Archived packet: #include "PlayerChangingMoveState.hpp"
// Archived packet: #include "PlayerChangingNickname.hpp"
// Archived packet: #include "PlayerChangingRadioPreset.hpp"
// Archived packet: #include "PlayerChangingSpectatedPlayer.hpp"
// Archived packet: #include "PlayerClosingGenerator.hpp"
// Archived packet: #include "PlayerConsumingItem.hpp"
// Archived packet: #include "PlayerDamagingDoor.hpp"
// Archived packet: #include "PlayerDamagingShootingTarget.hpp"
// Archived packet: #include "PlayerDamagingWindow.hpp"
// Archived packet: #include "PlayerDeactivatingWorkstation.hpp"
// Archived packet: #include "PlayerDestroying.hpp"
// Archived packet: #include "PlayerDrinkingCoffee.hpp"
// Archived packet: #include "PlayerDroppedAmmo.hpp"
// Archived packet: #include "PlayerDroppingAmmo.hpp"
// Archived packet: #include "PlayerDroppingItem.hpp"
// Archived packet: #include "PlayerDroppingNothing.hpp"
// Archived packet: #include "PlayerDryfiringWeapon.hpp"
// Archived packet: #include "PlayerEarningAchievement.hpp"
// Archived packet: #include "PlayerEnteringEnvironmentalHazard.hpp"
// Archived packet: #include "PlayerEnteringKillerCollision.hpp"
// Archived packet: #include "PlayerExitingEnvironmentalHazard.hpp"
#include "PlayerExplodingMicroHID.hpp"
// Archived packet: #include "PlayerFailingEscapePocketDimension.hpp"
// Archived packet: #include "PlayerFlippingCoin.hpp"
// Archived packet: #include "PlayerHealed.hpp"
// Archived packet: #include "PlayerHealing.hpp"
#include "PlayerHit.hpp"
// Archived packet: #include "PlayerInteracted.hpp"
// Archived packet: #include "PlayerInteractingLocker.hpp"
// Archived packet: #include "PlayerInteractingShootingTarget.hpp"
#include "PlayerIntercomSpeaking.hpp"
// Archived packet: #include "PlayerIssuingMute.hpp"
// Archived packet: #include "PlayerItemAdded.hpp"
// Archived packet: #include "PlayerItemRemoved.hpp"
// Archived packet: #include "PlayerJumping.hpp"
#include "PlayerKicked.hpp"
#include "PlayerKicking.hpp"
// Archived packet: #include "PlayerLanding.hpp"
// Archived packet: #include "PlayerMakingNoise.hpp"
// Archived packet: #include "PlayerMicroHIDOpeningDoor.hpp"
// Archived packet: #include "PlayerOpeningGenerator.hpp"
// Archived packet: #include "PlayerPlayingAudioLog.hpp"
// Archived packet: #include "PlayerPreAuthenticating.hpp"
// Archived packet: #include "PlayerReceivingEffect.hpp"
// Archived packet: #include "PlayerReceivingGunSound.hpp"
// Archived packet: #include "PlayerReceivingVoiceMessage.hpp"
// Archived packet: #include "PlayerReloadedWeapon.hpp"
// Archived packet: #include "PlayerReloadingWeapon.hpp"
// Archived packet: #include "PlayerRemovedHandcuffs.hpp"
// Archived packet: #include "PlayerRemovingHandcuffs.hpp"
// Archived packet: #include "PlayerReservedSlot.hpp"
// Archived packet: #include "PlayerRevokingMute.hpp"
// Archived packet: #include "PlayerRoomChanged.hpp"
// Archived packet: #include "PlayerRotatingRevolver.hpp"
// Archived packet: #include "PlayerSavingByAntiScp207.hpp"
// Archived packet: #include "PlayerScp1576TransmissionEnded.hpp"
// Archived packet: #include "PlayerSearchingPickup.hpp"
// Archived packet: #include "PlayerSendingAdminChatMessage.hpp"
// Archived packet: #include "PlayerSendingGunSound.hpp"
// Archived packet: #include "PlayerSendingValidCommand.hpp"
// Archived packet: #include "PlayerSentValidCommand.hpp"
// Archived packet: #include "PlayerSpawned.hpp"
// Archived packet: #include "PlayerSpawnedRagdoll.hpp"
// Archived packet: #include "PlayerSpawning.hpp"
// Archived packet: #include "PlayerSpawningRagdoll.hpp"
// Archived packet: #include "PlayerStayingOnEnvironmentalHazard.hpp"
// Archived packet: #include "PlayerStoppingGenerator.hpp"
// Archived packet: #include "PlayerThrowingRequest.hpp"
// Archived packet: #include "PlayerTogglingFlashlight.hpp"
// Archived packet: #include "PlayerTogglingNoClip.hpp"
// Archived packet: #include "PlayerTogglingOverwatch.hpp"
// Archived packet: #include "PlayerTogglingRadio.hpp"
// Archived packet: #include "PlayerTogglingWeaponFlashlight.hpp"
// Archived packet: #include "PlayerTransmitting.hpp"
#include "PlayerTriggeringTesla.hpp"
// Archived packet: #include "PlayerUnloadedWeapon.hpp"
// Archived packet: #include "PlayerUnloadingWeapon.hpp"
// Archived packet: #include "PlayerUnlockingGenerator.hpp"
// Archived packet: #include "PlayerUsingItem.hpp"
// Archived packet: #include "PlayerUsingItemCompleted.hpp"
// Archived packet: #include "PlayerUsingMicroHIDEnergy.hpp"
// Archived packet: #include "PlayerUsingRadioBattery.hpp"
// Archived packet: #include "PlayerVoiceChatting.hpp"
// Archived packet: #include "PlayerZoneChanged.hpp"
// Archived packet: #include "Scp049ActivatingSense.hpp"
#include "Scp049Attacking.hpp"
#include "Scp049FinishingRecall.hpp"
// Archived packet: #include "Scp049FinishingSense.hpp"
// Archived packet: #include "Scp049SendingCall.hpp"
// Archived packet: #include "Scp049StartingRecall.hpp"
// Archived packet: #include "Scp0492ConsumedCorpse.hpp"
// Archived packet: #include "Scp0492ConsumingCorpse.hpp"
// Archived packet: #include "Scp0492TriggeringBloodlust.hpp"
// Archived packet: #include "Scp079ChangingCamera.hpp"
// Archived packet: #include "Scp079ChangingSpeakerStatus.hpp"
// Archived packet: #include "Scp079ElevatorTeleporting.hpp"
// Archived packet: #include "Scp079GainingExperience.hpp"
// Archived packet: #include "Scp079GainingLevel.hpp"
// Archived packet: #include "Scp079InteractingTesla.hpp"
// Archived packet: #include "Scp079LockingDown.hpp"
// Archived packet: #include "Scp079LosingSignal.hpp"
// Archived packet: #include "Scp079LostSignal.hpp"
// Archived packet: #include "Scp079Pinging.hpp"
#include "Scp079Recontained.hpp"
#include "Scp079Recontaining.hpp"
#include "Scp079RoomBlackout.hpp"
// Archived packet: #include "Scp079TriggeringDoor.hpp"
#include "Scp079ZoneBlackout.hpp"
#include "Scp096AddingTarget.hpp"
// Archived packet: #include "Scp096CalmingDown.hpp"
#include "Scp096Charging.hpp"
#include "Scp096Enraging.hpp"
// Archived packet: #include "Scp096RemovingTarget.hpp"
// Archived packet: #include "Scp096StartPryingGate.hpp"
// Archived packet: #include "Scp096TryingNotToCry.hpp"
#include "Scp106Attacking.hpp"
// Archived packet: #include "Scp106ExitStalking.hpp"
// Archived packet: #include "Scp106Stalking.hpp"
#include "Scp106Teleporting.hpp"
// Archived packet: #include "Scp127GainedExperience.hpp"
// Archived packet: #include "Scp127GainingExperience.hpp"
// Archived packet: #include "Scp127Talked.hpp"
// Archived packet: #include "Scp127Talking.hpp"
// Archived packet: #include "Scp1344ChangedStatus.hpp"
// Archived packet: #include "Scp1344ChangingStatus.hpp"
// Archived packet: #include "Scp1344Deactivated.hpp"
// Archived packet: #include "Scp1344Deactivating.hpp"
// Archived packet: #include "Scp1344TryingDeactivating.hpp"
// Archived packet: #include "Scp1507AttackingDoor.hpp"
// Archived packet: #include "Scp1507Screaming.hpp"
// Archived packet: #include "Scp1507SpawningFlamingos.hpp"
// Archived packet: #include "Scp1507UsingTape.hpp"
// Archived packet: #include "Scp1509Resurrecting.hpp"
// Archived packet: #include "Scp1509TriggeringAttack.hpp"
// Archived packet: #include "Scp173AddingObserver.hpp"
// Archived packet: #include "Scp173BeingObserved.hpp"
// Archived packet: #include "Scp173Blinking.hpp"
// Archived packet: #include "Scp173BlinkingRequest.hpp"
#include "Scp173PlacingTantrum.hpp"
// Archived packet: #include "Scp173RemovedObserver.hpp"
// Archived packet: #include "Scp173UsingBreakneckSpeeds.hpp"
#include "Scp244DamagingScp244.hpp"
#include "Scp244OpeningScp244.hpp"
// Archived packet: #include "Scp244UsingScp244.hpp"
// Archived packet: #include "Scp2536FindingPosition.hpp"
// Archived packet: #include "Scp2536FoundPosition.hpp"
#include "Scp2536GrantingGift.hpp"
// Archived packet: #include "Scp2536OpeningGift.hpp"
// Archived packet: #include "Scp3114Dancing.hpp"
// Archived packet: #include "Scp3114Disguised.hpp"
// Archived packet: #include "Scp3114Disguising.hpp"
// Archived packet: #include "Scp3114Revealed.hpp"
// Archived packet: #include "Scp3114Revealing.hpp"
// Archived packet: #include "Scp3114Slapped.hpp"
#include "Scp3114Strangling.hpp"
// Archived packet: #include "Scp3114TryUseBody.hpp"
// Archived packet: #include "Scp3114VoiceLines.hpp"
// Archived packet: #include "Scp330DroppingScp330.hpp"
// Archived packet: #include "Scp330EatenScp330.hpp"
// Archived packet: #include "Scp330EatingScp330.hpp"
// Archived packet: #include "Scp330InteractingScp330.hpp"
// Archived packet: #include "Scp559Interacting.hpp"
// Archived packet: #include "Scp559Spawning.hpp"
// Archived packet: #include "Scp914Activating.hpp"
// Archived packet: #include "Scp914ChangingKnobSetting.hpp"
// Archived packet: #include "Scp914UpgradedInventoryItem.hpp"
// Archived packet: #include "Scp914UpgradedPickup.hpp"
// Archived packet: #include "Scp914UpgradingInventoryItem.hpp"
// Archived packet: #include "Scp914UpgradingPickup.hpp"
#include "Scp914UpgradingPlayer.hpp"
// Archived packet: #include "Scp939ChangingFocus.hpp"
#include "Scp939Clawed.hpp"
#include "Scp939Lunging.hpp"
// Archived packet: #include "Scp939PlacedAmnesticCloud.hpp"
#include "Scp939PlacingAmnesticCloud.hpp"
// Archived packet: #include "Scp939PlacingMimicPoint.hpp"
// Archived packet: #include "Scp939PlayingFootstep.hpp"
// Archived packet: #include "Scp939PlayingSound.hpp"
// Archived packet: #include "Scp939PlayingVoice.hpp"
// Archived packet: #include "Scp939SavingVoice.hpp"
// Archived packet: #include "Scp939UpdatedCloudState.hpp"
// Archived packet: #include "Scp939ValidatingVisibility.hpp"
// Archived packet: #include "ServerAddingUnitName.hpp"
// Archived packet: #include "ServerAllPlayersSpawned.hpp"
// Archived packet: #include "ServerChoosingStartTeamQueue.hpp"
#include "ServerCompletingObjective.hpp"
#include "ServerEndingRound.hpp"
// Archived packet: #include "ServerLocalReporting.hpp"
// Archived packet: #include "ServerReloadedConfigs.hpp"
// Archived packet: #include "ServerReloadedGameplay.hpp"
// Archived packet: #include "ServerReloadedPermissions.hpp"
// Archived packet: #include "ServerReloadedPlugins.hpp"
// Archived packet: #include "ServerReloadedRA.hpp"
// Archived packet: #include "ServerReloadedTranslations.hpp"
#include "ServerReportingCheater.hpp"
#include "ServerRespawnedTeam.hpp"
// Archived packet: #include "ServerRespawningTeam.hpp"
// Archived packet: #include "ServerSelectingRespawnTeam.hpp"
// Archived packet: #include "ServerUnbanned.hpp"
// Archived packet: #include "ServerUnbanning.hpp"
// Archived packet: #include "ServerWaitingForPlayers.hpp"
// Archived packet: #include "WarheadChangingLeverStatus.hpp"
#include "WarheadDeadmanSwitchInitiating.hpp"
#include "WarheadDetonated.hpp"
#include "WarheadDetonating.hpp"
#include "WarheadStarting.hpp"
#include "WarheadStopping.hpp"
#include "FlashGrenadeThrown.hpp"
#include "FlashGrenadeExploded.hpp"
#include "SCP268Used.hpp"
#include "SCP268Expired.hpp"

namespace Packet
{
    using Variant = std::variant<
                                Packet::Invalid::Data,
                                Packet::NewTick::Data,
                                Packet::Room::Data,
                                Packet::PlayerJoined::Data,
                                Packet::PlayerPosition::Data,
                                Packet::PlayerChangedRoles::Data,
                                Packet::PlayerLeft::Data,
                                Packet::DoorOpened::Data,
                                Packet::PlayerDied::Data,
                                Packet::DoorClosed::Data,
                                Packet::CancelChargingMicroHid::Data,
                                Packet::ChargingMicroHid::Data,
                                Packet::FiringMicroHid::Data,
                                Packet::PlayerEscaped::Data,
                                Packet::PlayerEscorted::Data,
                                Packet::VersionPacket::Data,
                                Packet::NtfWave::Data,
                                Packet::NtfMiniWave::Data,
                                Packet::CIWave::Data,
                                Packet::CIMiniWave::Data,
                                Packet::BallThrown::Data,
                                Packet::HitByBall::Data,
                                Packet::GrenadeThrown::Data,
                                Packet::GrenadeExploded::Data,
                                Packet::PickingUpItem::Data,
                                Packet::DroppedItem::Data,
                                Packet::PlayerHurt::Data,
                                Packet::PlayerShot::Data,
                                Packet::ItemUsed::Data,
                                Packet::PlayerAction::Data,
                                Packet::CassieSendingCassieMessage::Data,
                                Packet::ItemDisruptorFiring::Data,
                                Packet::ItemJailbirdChargeComplete::Data,
                                Packet::ItemPunching::Data,
                                Packet::MapAnnouncingDecontamination::Data,
                                Packet::MapAnnouncingScpTermination::Data,
                                Packet::MapDecontaminating::Data,
                                Packet::MapGeneratorActivating::Data,
                                Packet::MapPlacingBulletHole::Data,
                                Packet::PlayerBanned::Data,
                                Packet::PlayerExplodingMicroHID::Data,
                                Packet::PlayerHit::Data,
                                Packet::PlayerIntercomSpeaking::Data,
                                Packet::PlayerKicked::Data,
                                Packet::PlayerKicking::Data,
                                Packet::PlayerTriggeringTesla::Data,
                                Packet::Scp049Attacking::Data,
                                Packet::Scp049FinishingRecall::Data,
                                Packet::Scp079Recontained::Data,
                                Packet::Scp079Recontaining::Data,
                                Packet::Scp079RoomBlackout::Data,
                                Packet::Scp079ZoneBlackout::Data,
                                Packet::Scp096AddingTarget::Data,
                                Packet::Scp096Charging::Data,
                                Packet::Scp096Enraging::Data,
                                Packet::Scp106Attacking::Data,
                                Packet::Scp106Teleporting::Data,
                                Packet::Scp173PlacingTantrum::Data,
                                Packet::Scp244DamagingScp244::Data,
                                Packet::Scp244OpeningScp244::Data,
                                Packet::Scp2536GrantingGift::Data,
                                Packet::Scp3114Strangling::Data,
                                Packet::Scp914UpgradingPlayer::Data,
                                Packet::Scp939Clawed::Data,
                                Packet::Scp939Lunging::Data,
                                Packet::Scp939PlacingAmnesticCloud::Data,
                                Packet::ServerCompletingObjective::Data,
                                Packet::ServerEndingRound::Data,
                                Packet::ServerReportingCheater::Data,
                                Packet::ServerRespawnedTeam::Data,
                                Packet::WarheadDeadmanSwitchInitiating::Data,
                                Packet::WarheadDetonated::Data,
                                Packet::WarheadDetonating::Data,
                                Packet::WarheadStarting::Data,
                                Packet::WarheadStopping::Data,
                                Packet::FlashGrenadeThrown::Data,
                                Packet::FlashGrenadeExploded::Data,
                                Packet::SCP268Used::Data,
                                Packet::SCP268Expired::Data>;
                                // Archived packet type: Packet::ItemCackling::Data
                                // Archived packet type: Packet::ItemChangingAmmo::Data
                                // Archived packet type: Packet::ItemChangingAttachments::Data
                                // Archived packet type: Packet::ItemChangingMicroHIDPickupState::Data
                                // Archived packet type: Packet::ItemChargingJailbird::Data
                                // Archived packet type: Packet::ItemInspectedItem::Data
                                // Archived packet type: Packet::ItemInspectingItem::Data
                                // Archived packet type: Packet::ItemJailbirdChangedWearState::Data
                                // Archived packet type: Packet::ItemJailbirdChangingWearState::Data
                                // Archived packet type: Packet::ItemKeycardInteracting::Data
                                // Archived packet type: Packet::ItemReceivingPreference::Data
                                // Archived packet type: Packet::ItemSwinging::Data
                                // Archived packet type: Packet::ItemUsingRadioPickupBattery::Data
                                // Archived packet type: Packet::MapChangedIntoGrenade::Data
                                // Archived packet type: Packet::MapChangingIntoGrenade::Data
                                // Archived packet type: Packet::MapElevatorSequencesUpdated::Data
                                // Archived packet type: Packet::MapFillingLocker::Data
                                // Archived packet type: Packet::MapGenerated::Data
                                // Archived packet type: Packet::MapGenerating::Data
                                // Archived packet type: Packet::MapPickupAdded::Data
                                // Archived packet type: Packet::MapPickupDestroyed::Data
                                // Archived packet type: Packet::MapPlacingPickupIntoPocketDimension::Data
                                // Archived packet type: Packet::MapScp244Spawning::Data
                                // Archived packet type: Packet::MapSpawningGrenadeEffect::Data
                                // Archived packet type: Packet::MapSpawningItem::Data
                                // Archived packet type: Packet::MapSpawningRoomConnector::Data
                                // Archived packet type: Packet::MapSpawningTeamVehicle::Data
                                // Archived packet type: Packet::MapTurningOffLights::Data
                                // Archived packet type: Packet::PlayerActivatingWorkstation::Data
                                // Archived packet type: Packet::PlayerAimingDownSight::Data
                                // Archived packet type: Packet::PlayerBanning::Data
                                // Archived packet type: Packet::PlayerCancelledItemUse::Data
                                // Archived packet type: Packet::PlayerCancellingItemUse::Data
                                // Archived packet type: Packet::PlayerChangedEmotion::Data
                                // Archived packet type: Packet::PlayerChangedItem::Data
                                // Archived packet type: Packet::PlayerChangedRatio::Data
                                // Archived packet type: Packet::PlayerChangingDangerState::Data
                                // Archived packet type: Packet::PlayerChangingDisruptorMode::Data
                                // Archived packet type: Packet::PlayerChangingEmotion::Data
                                // Archived packet type: Packet::PlayerChangingGroup::Data
                                // Archived packet type: Packet::PlayerChangingItem::Data
                                // Archived packet type: Packet::PlayerChangingMoveState::Data
                                // Archived packet type: Packet::PlayerChangingNickname::Data
                                // Archived packet type: Packet::PlayerChangingRadioPreset::Data
                                // Archived packet type: Packet::PlayerChangingSpectatedPlayer::Data
                                // Archived packet type: Packet::PlayerClosingGenerator::Data
                                // Archived packet type: Packet::PlayerConsumingItem::Data
                                // Archived packet type: Packet::PlayerDamagingDoor::Data
                                // Archived packet type: Packet::PlayerDamagingShootingTarget::Data
                                // Archived packet type: Packet::PlayerDamagingWindow::Data
                                // Archived packet type: Packet::PlayerDeactivatingWorkstation::Data
                                // Archived packet type: Packet::PlayerDestroying::Data
                                // Archived packet type: Packet::PlayerDrinkingCoffee::Data
                                // Archived packet type: Packet::PlayerDroppedAmmo::Data
                                // Archived packet type: Packet::PlayerDroppingAmmo::Data
                                // Archived packet type: Packet::PlayerDroppingItem::Data
                                // Archived packet type: Packet::PlayerDroppingNothing::Data
                                // Archived packet type: Packet::PlayerDryfiringWeapon::Data
                                // Archived packet type: Packet::PlayerEarningAchievement::Data
                                // Archived packet type: Packet::PlayerEnteringEnvironmentalHazard::Data
                                // Archived packet type: Packet::PlayerEnteringKillerCollision::Data
                                // Archived packet type: Packet::PlayerExitingEnvironmentalHazard::Data
                                // Archived packet type: Packet::PlayerFailingEscapePocketDimension::Data
                                // Archived packet type: Packet::PlayerFlippingCoin::Data
                                // Archived packet type: Packet::PlayerHealed::Data
                                // Archived packet type: Packet::PlayerHealing::Data
                                // Archived packet type: Packet::PlayerInteracted::Data
                                // Archived packet type: Packet::PlayerInteractingLocker::Data
                                // Archived packet type: Packet::PlayerInteractingShootingTarget::Data
                                // Archived packet type: Packet::PlayerIssuingMute::Data
                                // Archived packet type: Packet::PlayerItemAdded::Data
                                // Archived packet type: Packet::PlayerItemRemoved::Data
                                // Archived packet type: Packet::PlayerJumping::Data
                                // Archived packet type: Packet::PlayerLanding::Data
                                // Archived packet type: Packet::PlayerMakingNoise::Data
                                // Archived packet type: Packet::PlayerMicroHIDOpeningDoor::Data
                                // Archived packet type: Packet::PlayerOpeningGenerator::Data
                                // Archived packet type: Packet::PlayerPlayingAudioLog::Data
                                // Archived packet type: Packet::PlayerPreAuthenticating::Data
                                // Archived packet type: Packet::PlayerReceivingEffect::Data
                                // Archived packet type: Packet::PlayerReceivingGunSound::Data
                                // Archived packet type: Packet::PlayerReceivingVoiceMessage::Data
                                // Archived packet type: Packet::PlayerReloadedWeapon::Data
                                // Archived packet type: Packet::PlayerReloadingWeapon::Data
                                // Archived packet type: Packet::PlayerRemovedHandcuffs::Data
                                // Archived packet type: Packet::PlayerRemovingHandcuffs::Data
                                // Archived packet type: Packet::PlayerReservedSlot::Data
                                // Archived packet type: Packet::PlayerRevokingMute::Data
                                // Archived packet type: Packet::PlayerRoomChanged::Data
                                // Archived packet type: Packet::PlayerRotatingRevolver::Data
                                // Archived packet type: Packet::PlayerSavingByAntiScp207::Data
                                // Archived packet type: Packet::PlayerScp1576TransmissionEnded::Data
                                // Archived packet type: Packet::PlayerSearchingPickup::Data
                                // Archived packet type: Packet::PlayerSendingAdminChatMessage::Data
                                // Archived packet type: Packet::PlayerSendingGunSound::Data
                                // Archived packet type: Packet::PlayerSendingValidCommand::Data
                                // Archived packet type: Packet::PlayerSentValidCommand::Data
                                // Archived packet type: Packet::PlayerSpawned::Data
                                // Archived packet type: Packet::PlayerSpawnedRagdoll::Data
                                // Archived packet type: Packet::PlayerSpawning::Data
                                // Archived packet type: Packet::PlayerSpawningRagdoll::Data
                                // Archived packet type: Packet::PlayerStayingOnEnvironmentalHazard::Data
                                // Archived packet type: Packet::PlayerStoppingGenerator::Data
                                // Archived packet type: Packet::PlayerThrowingRequest::Data
                                // Archived packet type: Packet::PlayerTogglingFlashlight::Data
                                // Archived packet type: Packet::PlayerTogglingNoClip::Data
                                // Archived packet type: Packet::PlayerTogglingOverwatch::Data
                                // Archived packet type: Packet::PlayerTogglingRadio::Data
                                // Archived packet type: Packet::PlayerTogglingWeaponFlashlight::Data
                                // Archived packet type: Packet::PlayerTransmitting::Data
                                // Archived packet type: Packet::PlayerUnloadedWeapon::Data
                                // Archived packet type: Packet::PlayerUnloadingWeapon::Data
                                // Archived packet type: Packet::PlayerUnlockingGenerator::Data
                                // Archived packet type: Packet::PlayerUsingItem::Data
                                // Archived packet type: Packet::PlayerUsingItemCompleted::Data
                                // Archived packet type: Packet::PlayerUsingMicroHIDEnergy::Data
                                // Archived packet type: Packet::PlayerUsingRadioBattery::Data
                                // Archived packet type: Packet::PlayerVoiceChatting::Data
                                // Archived packet type: Packet::PlayerZoneChanged::Data
                                // Archived packet type: Packet::Scp049ActivatingSense::Data
                                // Archived packet type: Packet::Scp049FinishingSense::Data
                                // Archived packet type: Packet::Scp049SendingCall::Data
                                // Archived packet type: Packet::Scp049StartingRecall::Data
                                // Archived packet type: Packet::Scp0492ConsumedCorpse::Data
                                // Archived packet type: Packet::Scp0492ConsumingCorpse::Data
                                // Archived packet type: Packet::Scp0492TriggeringBloodlust::Data
                                // Archived packet type: Packet::Scp079ChangingCamera::Data
                                // Archived packet type: Packet::Scp079ChangingSpeakerStatus::Data
                                // Archived packet type: Packet::Scp079ElevatorTeleporting::Data
                                // Archived packet type: Packet::Scp079GainingExperience::Data
                                // Archived packet type: Packet::Scp079GainingLevel::Data
                                // Archived packet type: Packet::Scp079InteractingTesla::Data
                                // Archived packet type: Packet::Scp079LockingDown::Data
                                // Archived packet type: Packet::Scp079LosingSignal::Data
                                // Archived packet type: Packet::Scp079LostSignal::Data
                                // Archived packet type: Packet::Scp079Pinging::Data
                                // Archived packet type: Packet::Scp079TriggeringDoor::Data
                                // Archived packet type: Packet::Scp096CalmingDown::Data
                                // Archived packet type: Packet::Scp096RemovingTarget::Data
                                // Archived packet type: Packet::Scp096StartPryingGate::Data
                                // Archived packet type: Packet::Scp096TryingNotToCry::Data
                                // Archived packet type: Packet::Scp106ExitStalking::Data
                                // Archived packet type: Packet::Scp106Stalking::Data
                                // Archived packet type: Packet::Scp127GainedExperience::Data
                                // Archived packet type: Packet::Scp127GainingExperience::Data
                                // Archived packet type: Packet::Scp127Talked::Data
                                // Archived packet type: Packet::Scp127Talking::Data
                                // Archived packet type: Packet::Scp1344ChangedStatus::Data
                                // Archived packet type: Packet::Scp1344ChangingStatus::Data
                                // Archived packet type: Packet::Scp1344Deactivated::Data
                                // Archived packet type: Packet::Scp1344Deactivating::Data
                                // Archived packet type: Packet::Scp1344TryingDeactivating::Data
                                // Archived packet type: Packet::Scp1507AttackingDoor::Data
                                // Archived packet type: Packet::Scp1507Screaming::Data
                                // Archived packet type: Packet::Scp1507SpawningFlamingos::Data
                                // Archived packet type: Packet::Scp1507UsingTape::Data
                                // Archived packet type: Packet::Scp1509Resurrecting::Data
                                // Archived packet type: Packet::Scp1509TriggeringAttack::Data
                                // Archived packet type: Packet::Scp173AddingObserver::Data
                                // Archived packet type: Packet::Scp173BeingObserved::Data
                                // Archived packet type: Packet::Scp173Blinking::Data
                                // Archived packet type: Packet::Scp173BlinkingRequest::Data
                                // Archived packet type: Packet::Scp173RemovedObserver::Data
                                // Archived packet type: Packet::Scp173UsingBreakneckSpeeds::Data
                                // Archived packet type: Packet::Scp244UsingScp244::Data
                                // Archived packet type: Packet::Scp2536FindingPosition::Data
                                // Archived packet type: Packet::Scp2536FoundPosition::Data
                                // Archived packet type: Packet::Scp2536OpeningGift::Data
                                // Archived packet type: Packet::Scp3114Dancing::Data
                                // Archived packet type: Packet::Scp3114Disguised::Data
                                // Archived packet type: Packet::Scp3114Disguising::Data
                                // Archived packet type: Packet::Scp3114Revealed::Data
                                // Archived packet type: Packet::Scp3114Revealing::Data
                                // Archived packet type: Packet::Scp3114Slapped::Data
                                // Archived packet type: Packet::Scp3114TryUseBody::Data
                                // Archived packet type: Packet::Scp3114VoiceLines::Data
                                // Archived packet type: Packet::Scp330DroppingScp330::Data
                                // Archived packet type: Packet::Scp330EatenScp330::Data
                                // Archived packet type: Packet::Scp330EatingScp330::Data
                                // Archived packet type: Packet::Scp330InteractingScp330::Data
                                // Archived packet type: Packet::Scp559Interacting::Data
                                // Archived packet type: Packet::Scp559Spawning::Data
                                // Archived packet type: Packet::Scp914Activating::Data
                                // Archived packet type: Packet::Scp914ChangingKnobSetting::Data
                                // Archived packet type: Packet::Scp914UpgradedInventoryItem::Data
                                // Archived packet type: Packet::Scp914UpgradedPickup::Data
                                // Archived packet type: Packet::Scp914UpgradingInventoryItem::Data
                                // Archived packet type: Packet::Scp914UpgradingPickup::Data
                                // Archived packet type: Packet::Scp939ChangingFocus::Data
                                // Archived packet type: Packet::Scp939PlacedAmnesticCloud::Data
                                // Archived packet type: Packet::Scp939PlacingMimicPoint::Data
                                // Archived packet type: Packet::Scp939PlayingFootstep::Data
                                // Archived packet type: Packet::Scp939PlayingSound::Data
                                // Archived packet type: Packet::Scp939PlayingVoice::Data
                                // Archived packet type: Packet::Scp939SavingVoice::Data
                                // Archived packet type: Packet::Scp939UpdatedCloudState::Data
                                // Archived packet type: Packet::Scp939ValidatingVisibility::Data
                                // Archived packet type: Packet::ServerAddingUnitName::Data
                                // Archived packet type: Packet::ServerAllPlayersSpawned::Data
                                // Archived packet type: Packet::ServerChoosingStartTeamQueue::Data
                                // Archived packet type: Packet::ServerLocalReporting::Data
                                // Archived packet type: Packet::ServerReloadedConfigs::Data
                                // Archived packet type: Packet::ServerReloadedGameplay::Data
                                // Archived packet type: Packet::ServerReloadedPermissions::Data
                                // Archived packet type: Packet::ServerReloadedPlugins::Data
                                // Archived packet type: Packet::ServerReloadedRA::Data
                                // Archived packet type: Packet::ServerReloadedTranslations::Data
                                // Archived packet type: Packet::ServerRespawningTeam::Data
                                // Archived packet type: Packet::ServerSelectingRespawnTeam::Data
                                // Archived packet type: Packet::ServerUnbanned::Data
                                // Archived packet type: Packet::ServerUnbanning::Data
                                // Archived packet type: Packet::ServerWaitingForPlayers::Data
                                // Archived packet type: Packet::WarheadChangingLeverStatus::Data
    Variant Resolve(Events::EventEnum event, const std::vector<uint8_t> &data);

}