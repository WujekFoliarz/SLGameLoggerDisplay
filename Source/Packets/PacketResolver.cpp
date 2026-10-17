#include "PacketResolver.hpp"
#include "PacketReader.hpp"
#include <print>

Packet::Variant Packet::Resolve(Events::EventEnum event, const std::vector<uint8_t> &data)
{
    switch (event)
    {
    case Events::EventEnum::NewTick:
        return NewTick::GetResult(data);
    case Events::EventEnum::Room:
        return Room::GetResult(data);
    case Events::EventEnum::PlayerJoined:
        return PlayerJoined::GetResult(data);
    case Events::EventEnum::PlayerLeft:
        return PlayerLeft::GetResult(data);
    case Events::EventEnum::PlayerPosition:
        return PlayerPosition::GetResult(data);
    case Events::EventEnum::PlayerChangedRoles:
        return PlayerChangedRoles::GetResult(data);
    case Events::EventEnum::DoorOpened:
        return DoorOpened::GetResult(data);
    case Events::EventEnum::DoorClosed:
        return DoorClosed::GetResult(data);
    case Events::EventEnum::PlayerDied:
        return PlayerDied::GetResult(data);
    case Events::EventEnum::MicroHidCanceledCharging:
        return CancelChargingMicroHid::GetResult(data);
    case Events::EventEnum::MicroHidCharging:
        return ChargingMicroHid::GetResult(data);
    case Events::EventEnum::MicroHidFiring:
        return FiringMicroHid::GetResult(data);
    case Events::EventEnum::PlayerEscaped:
        return PlayerEscaped::GetResult(data);
    case Events::EventEnum::PlayerEscorted:
        return PlayerEscorted::GetResult(data);
    case Events::EventEnum::Version:
        return VersionPacket::GetResult(data);
    case Events::EventEnum::NtfWave:
        return NtfWave::GetResult(data);
    case Events::EventEnum::NtfMiniWave:
        return NtfMiniWave::GetResult(data);
    case Events::EventEnum::CIWave:
        return CIWave::GetResult(data);
    case Events::EventEnum::CIMiniWave:
        return CIMiniWave::GetResult(data);
    case Events::EventEnum::BallThrown:
        return BallThrown::GetResult(data);
    case Events::EventEnum::HitByBall:
        return HitByBall::GetResult(data);
    case Events::EventEnum::GrenadeThrown:
        return GrenadeThrown::GetResult(data);
    case Events::EventEnum::GrenadeExploded:
        return GrenadeExploded::GetResult(data);
    case Events::EventEnum::PickingUpItem:
        return PickingUpItem::GetResult(data);
    case Events::EventEnum::DroppedItem:
        return DroppedItem::GetResult(data);
    case Events::EventEnum::PlayerHurt:
        return PlayerHurt::GetResult(data);
    case Events::EventEnum::PlayerShot:
        return PlayerShot::GetResult(data);
    case Events::EventEnum::ItemUsed:
        return ItemUsed::GetResult(data);
    case Events::EventEnum::PlayerActivatedGenerator:
    case Events::EventEnum::PlayerActivatedWarheadPanel:
    case Events::EventEnum::PlayerCalledElevator:
    case Events::EventEnum::PlayerUsedElevator:
    case Events::EventEnum::PlayerPressedEmergencyDoorButton:
    case Events::EventEnum::PlayerHandcuffed:
    case Events::EventEnum::PlayerSentToPocketDimension:
    case Events::EventEnum::PlayerEscapedPocketDimension:
        return PlayerAction::GetResult(event, data);
    case Events::EventEnum::CassieSendingCassieMessage:
        return CassieSendingCassieMessage::GetResult(data);
    // Archived event resolver: ItemCackling -> ItemCackling::GetResult(data);
    // Archived event resolver: ItemChangingAmmo -> ItemChangingAmmo::GetResult(data);
    // Archived event resolver: ItemChangingAttachments -> ItemChangingAttachments::GetResult(data);
    // Archived event resolver: ItemChangingMicroHIDPickupState -> ItemChangingMicroHIDPickupState::GetResult(data);
    // Archived event resolver: ItemChargingJailbird -> ItemChargingJailbird::GetResult(data);
    case Events::EventEnum::ItemDisruptorFiring:
        return ItemDisruptorFiring::GetResult(data);
    // Archived event resolver: ItemInspectedItem -> ItemInspectedItem::GetResult(data);
    // Archived event resolver: ItemInspectingItem -> ItemInspectingItem::GetResult(data);
    // Archived event resolver: ItemJailbirdChangedWearState -> ItemJailbirdChangedWearState::GetResult(data);
    // Archived event resolver: ItemJailbirdChangingWearState -> ItemJailbirdChangingWearState::GetResult(data);
    case Events::EventEnum::ItemJailbirdChargeComplete:
        return ItemJailbirdChargeComplete::GetResult(data);
    // Archived event resolver: ItemKeycardInteracting -> ItemKeycardInteracting::GetResult(data);
    case Events::EventEnum::ItemPunching:
        return ItemPunching::GetResult(data);
    // Archived event resolver: ItemReceivingPreference -> ItemReceivingPreference::GetResult(data);
    // Archived event resolver: ItemSwinging -> ItemSwinging::GetResult(data);
    // Archived event resolver: ItemUsingRadioPickupBattery -> ItemUsingRadioPickupBattery::GetResult(data);
    case Events::EventEnum::MapAnnouncingDecontamination:
        return MapAnnouncingDecontamination::GetResult(data);
    case Events::EventEnum::MapAnnouncingScpTermination:
        return MapAnnouncingScpTermination::GetResult(data);
    // Archived event resolver: MapChangedIntoGrenade -> MapChangedIntoGrenade::GetResult(data);
    // Archived event resolver: MapChangingIntoGrenade -> MapChangingIntoGrenade::GetResult(data);
    case Events::EventEnum::MapDecontaminating:
        return MapDecontaminating::GetResult(data);
    // Archived event resolver: MapElevatorSequencesUpdated -> MapElevatorSequencesUpdated::GetResult(data);
    // Archived event resolver: MapFillingLocker -> MapFillingLocker::GetResult(data);
    // Archived event resolver: MapGenerated -> MapGenerated::GetResult(data);
    // Archived event resolver: MapGenerating -> MapGenerating::GetResult(data);
    case Events::EventEnum::MapGeneratorActivating:
        return MapGeneratorActivating::GetResult(data);
    // Archived event resolver: MapPickupAdded -> MapPickupAdded::GetResult(data);
    // Archived event resolver: MapPickupDestroyed -> MapPickupDestroyed::GetResult(data);
    case Events::EventEnum::MapPlacingBulletHole:
        return MapPlacingBulletHole::GetResult(data);
    // Archived event resolver: MapPlacingPickupIntoPocketDimension -> MapPlacingPickupIntoPocketDimension::GetResult(data);
    // Archived event resolver: MapScp244Spawning -> MapScp244Spawning::GetResult(data);
    // Archived event resolver: MapSpawningGrenadeEffect -> MapSpawningGrenadeEffect::GetResult(data);
    // Archived event resolver: MapSpawningItem -> MapSpawningItem::GetResult(data);
    // Archived event resolver: MapSpawningRoomConnector -> MapSpawningRoomConnector::GetResult(data);
    // Archived event resolver: MapSpawningTeamVehicle -> MapSpawningTeamVehicle::GetResult(data);
    // Archived event resolver: MapTurningOffLights -> MapTurningOffLights::GetResult(data);
    // Archived event resolver: PlayerActivatingWorkstation -> PlayerActivatingWorkstation::GetResult(data);
    // Archived event resolver: PlayerAimingDownSight -> PlayerAimingDownSight::GetResult(data);
    case Events::EventEnum::PlayerBanned:
        return PlayerBanned::GetResult(data);
    // Archived event resolver: PlayerBanning -> PlayerBanning::GetResult(data);
    // Archived event resolver: PlayerCancelledItemUse -> PlayerCancelledItemUse::GetResult(data);
    // Archived event resolver: PlayerCancellingItemUse -> PlayerCancellingItemUse::GetResult(data);
    // Archived event resolver: PlayerChangedEmotion -> PlayerChangedEmotion::GetResult(data);
    // Archived event resolver: PlayerChangedItem -> PlayerChangedItem::GetResult(data);
    // Archived event resolver: PlayerChangedRatio -> PlayerChangedRatio::GetResult(data);
    // Archived event resolver: PlayerChangingDangerState -> PlayerChangingDangerState::GetResult(data);
    // Archived event resolver: PlayerChangingDisruptorMode -> PlayerChangingDisruptorMode::GetResult(data);
    // Archived event resolver: PlayerChangingEmotion -> PlayerChangingEmotion::GetResult(data);
    // Archived event resolver: PlayerChangingGroup -> PlayerChangingGroup::GetResult(data);
    // Archived event resolver: PlayerChangingItem -> PlayerChangingItem::GetResult(data);
    // Archived event resolver: PlayerChangingMoveState -> PlayerChangingMoveState::GetResult(data);
    // Archived event resolver: PlayerChangingNickname -> PlayerChangingNickname::GetResult(data);
    // Archived event resolver: PlayerChangingRadioPreset -> PlayerChangingRadioPreset::GetResult(data);
    // Archived event resolver: PlayerChangingSpectatedPlayer -> PlayerChangingSpectatedPlayer::GetResult(data);
    // Archived event resolver: PlayerClosingGenerator -> PlayerClosingGenerator::GetResult(data);
    // Archived event resolver: PlayerConsumingItem -> PlayerConsumingItem::GetResult(data);
    // Archived event resolver: PlayerDamagingDoor -> PlayerDamagingDoor::GetResult(data);
    // Archived event resolver: PlayerDamagingShootingTarget -> PlayerDamagingShootingTarget::GetResult(data);
    // Archived event resolver: PlayerDamagingWindow -> PlayerDamagingWindow::GetResult(data);
    // Archived event resolver: PlayerDeactivatingWorkstation -> PlayerDeactivatingWorkstation::GetResult(data);
    // Archived event resolver: PlayerDestroying -> PlayerDestroying::GetResult(data);
    // Archived event resolver: PlayerDrinkingCoffee -> PlayerDrinkingCoffee::GetResult(data);
    // Archived event resolver: PlayerDroppedAmmo -> PlayerDroppedAmmo::GetResult(data);
    // Archived event resolver: PlayerDroppingAmmo -> PlayerDroppingAmmo::GetResult(data);
    // Archived event resolver: PlayerDroppingItem -> PlayerDroppingItem::GetResult(data);
    // Archived event resolver: PlayerDroppingNothing -> PlayerDroppingNothing::GetResult(data);
    // Archived event resolver: PlayerDryfiringWeapon -> PlayerDryfiringWeapon::GetResult(data);
    // Archived event resolver: PlayerEarningAchievement -> PlayerEarningAchievement::GetResult(data);
    // Archived event resolver: PlayerEnteringEnvironmentalHazard -> PlayerEnteringEnvironmentalHazard::GetResult(data);
    // Archived event resolver: PlayerEnteringKillerCollision -> PlayerEnteringKillerCollision::GetResult(data);
    // Archived event resolver: PlayerExitingEnvironmentalHazard -> PlayerExitingEnvironmentalHazard::GetResult(data);
    case Events::EventEnum::PlayerExplodingMicroHID:
        return PlayerExplodingMicroHID::GetResult(data);
    // Archived event resolver: PlayerFailingEscapePocketDimension -> PlayerFailingEscapePocketDimension::GetResult(data);
    // Archived event resolver: PlayerFlippingCoin -> PlayerFlippingCoin::GetResult(data);
    // Archived event resolver: PlayerHealed -> PlayerHealed::GetResult(data);
    // Archived event resolver: PlayerHealing -> PlayerHealing::GetResult(data);
    case Events::EventEnum::PlayerHit:
        return PlayerHit::GetResult(data);
    // Archived event resolver: PlayerInteracted -> PlayerInteracted::GetResult(data);
    // Archived event resolver: PlayerInteractingLocker -> PlayerInteractingLocker::GetResult(data);
    // Archived event resolver: PlayerInteractingShootingTarget -> PlayerInteractingShootingTarget::GetResult(data);
    case Events::EventEnum::PlayerIntercomSpeaking:
        return PlayerIntercomSpeaking::GetResult(data);
    // Archived event resolver: PlayerIssuingMute -> PlayerIssuingMute::GetResult(data);
    // Archived event resolver: PlayerItemAdded -> PlayerItemAdded::GetResult(data);
    // Archived event resolver: PlayerItemRemoved -> PlayerItemRemoved::GetResult(data);
    // Archived event resolver: PlayerJumping -> PlayerJumping::GetResult(data);
    case Events::EventEnum::PlayerKicked:
        return PlayerKicked::GetResult(data);
    case Events::EventEnum::PlayerKicking:
        return PlayerKicking::GetResult(data);
    // Archived event resolver: PlayerLanding -> PlayerLanding::GetResult(data);
    // Archived event resolver: PlayerMakingNoise -> PlayerMakingNoise::GetResult(data);
    // Archived event resolver: PlayerMicroHIDOpeningDoor -> PlayerMicroHIDOpeningDoor::GetResult(data);
    // Archived event resolver: PlayerOpeningGenerator -> PlayerOpeningGenerator::GetResult(data);
    // Archived event resolver: PlayerPlayingAudioLog -> PlayerPlayingAudioLog::GetResult(data);
    // Archived event resolver: PlayerPreAuthenticating -> PlayerPreAuthenticating::GetResult(data);
    // Archived event resolver: PlayerReceivingEffect -> PlayerReceivingEffect::GetResult(data);
    // Archived event resolver: PlayerReceivingGunSound -> PlayerReceivingGunSound::GetResult(data);
    // Archived event resolver: PlayerReceivingVoiceMessage -> PlayerReceivingVoiceMessage::GetResult(data);
    // Archived event resolver: PlayerReloadedWeapon -> PlayerReloadedWeapon::GetResult(data);
    // Archived event resolver: PlayerReloadingWeapon -> PlayerReloadingWeapon::GetResult(data);
    // Archived event resolver: PlayerRemovedHandcuffs -> PlayerRemovedHandcuffs::GetResult(data);
    // Archived event resolver: PlayerRemovingHandcuffs -> PlayerRemovingHandcuffs::GetResult(data);
    // Archived event resolver: PlayerReservedSlot -> PlayerReservedSlot::GetResult(data);
    // Archived event resolver: PlayerRevokingMute -> PlayerRevokingMute::GetResult(data);
    // Archived event resolver: PlayerRoomChanged -> PlayerRoomChanged::GetResult(data);
    // Archived event resolver: PlayerRotatingRevolver -> PlayerRotatingRevolver::GetResult(data);
    // Archived event resolver: PlayerSavingByAntiScp207 -> PlayerSavingByAntiScp207::GetResult(data);
    // Archived event resolver: PlayerScp1576TransmissionEnded -> PlayerScp1576TransmissionEnded::GetResult(data);
    // Archived event resolver: PlayerSearchingPickup -> PlayerSearchingPickup::GetResult(data);
    // Archived event resolver: PlayerSendingAdminChatMessage -> PlayerSendingAdminChatMessage::GetResult(data);
    // Archived event resolver: PlayerSendingGunSound -> PlayerSendingGunSound::GetResult(data);
    // Archived event resolver: PlayerSendingValidCommand -> PlayerSendingValidCommand::GetResult(data);
    // Archived event resolver: PlayerSentValidCommand -> PlayerSentValidCommand::GetResult(data);
    // Archived event resolver: PlayerSpawned -> PlayerSpawned::GetResult(data);
    // Archived event resolver: PlayerSpawnedRagdoll -> PlayerSpawnedRagdoll::GetResult(data);
    // Archived event resolver: PlayerSpawning -> PlayerSpawning::GetResult(data);
    // Archived event resolver: PlayerSpawningRagdoll -> PlayerSpawningRagdoll::GetResult(data);
    // Archived event resolver: PlayerStayingOnEnvironmentalHazard -> PlayerStayingOnEnvironmentalHazard::GetResult(data);
    // Archived event resolver: PlayerStoppingGenerator -> PlayerStoppingGenerator::GetResult(data);
    // Archived event resolver: PlayerThrowingRequest -> PlayerThrowingRequest::GetResult(data);
    // Archived event resolver: PlayerTogglingFlashlight -> PlayerTogglingFlashlight::GetResult(data);
    // Archived event resolver: PlayerTogglingNoClip -> PlayerTogglingNoClip::GetResult(data);
    // Archived event resolver: PlayerTogglingOverwatch -> PlayerTogglingOverwatch::GetResult(data);
    // Archived event resolver: PlayerTogglingRadio -> PlayerTogglingRadio::GetResult(data);
    // Archived event resolver: PlayerTogglingWeaponFlashlight -> PlayerTogglingWeaponFlashlight::GetResult(data);
    // Archived event resolver: PlayerTransmitting -> PlayerTransmitting::GetResult(data);
    case Events::EventEnum::PlayerTriggeringTesla:
        return PlayerTriggeringTesla::GetResult(data);
    // Archived event resolver: PlayerUnloadedWeapon -> PlayerUnloadedWeapon::GetResult(data);
    // Archived event resolver: PlayerUnloadingWeapon -> PlayerUnloadingWeapon::GetResult(data);
    // Archived event resolver: PlayerUnlockingGenerator -> PlayerUnlockingGenerator::GetResult(data);
    // Archived event resolver: PlayerUsingItem -> PlayerUsingItem::GetResult(data);
    // Archived event resolver: PlayerUsingItemCompleted -> PlayerUsingItemCompleted::GetResult(data);
    // Archived event resolver: PlayerUsingMicroHIDEnergy -> PlayerUsingMicroHIDEnergy::GetResult(data);
    // Archived event resolver: PlayerUsingRadioBattery -> PlayerUsingRadioBattery::GetResult(data);
    // Archived event resolver: PlayerVoiceChatting -> PlayerVoiceChatting::GetResult(data);
    // Archived event resolver: PlayerZoneChanged -> PlayerZoneChanged::GetResult(data);
    // Archived event resolver: Scp049ActivatingSense -> Scp049ActivatingSense::GetResult(data);
    case Events::EventEnum::Scp049Attacking:
        return Scp049Attacking::GetResult(data);
    case Events::EventEnum::Scp049FinishingRecall:
        return Scp049FinishingRecall::GetResult(data);
    // Archived event resolver: Scp049FinishingSense -> Scp049FinishingSense::GetResult(data);
    // Archived event resolver: Scp049SendingCall -> Scp049SendingCall::GetResult(data);
    // Archived event resolver: Scp049StartingRecall -> Scp049StartingRecall::GetResult(data);
    // Archived event resolver: Scp0492ConsumedCorpse -> Scp0492ConsumedCorpse::GetResult(data);
    // Archived event resolver: Scp0492ConsumingCorpse -> Scp0492ConsumingCorpse::GetResult(data);
    // Archived event resolver: Scp0492TriggeringBloodlust -> Scp0492TriggeringBloodlust::GetResult(data);
    // Archived event resolver: Scp079ChangingCamera -> Scp079ChangingCamera::GetResult(data);
    // Archived event resolver: Scp079ChangingSpeakerStatus -> Scp079ChangingSpeakerStatus::GetResult(data);
    // Archived event resolver: Scp079ElevatorTeleporting -> Scp079ElevatorTeleporting::GetResult(data);
    // Archived event resolver: Scp079GainingExperience -> Scp079GainingExperience::GetResult(data);
    // Archived event resolver: Scp079GainingLevel -> Scp079GainingLevel::GetResult(data);
    // Archived event resolver: Scp079InteractingTesla -> Scp079InteractingTesla::GetResult(data);
    // Archived event resolver: Scp079LockingDown -> Scp079LockingDown::GetResult(data);
    // Archived event resolver: Scp079LosingSignal -> Scp079LosingSignal::GetResult(data);
    // Archived event resolver: Scp079LostSignal -> Scp079LostSignal::GetResult(data);
    // Archived event resolver: Scp079Pinging -> Scp079Pinging::GetResult(data);
    case Events::EventEnum::Scp079Recontained:
        return Scp079Recontained::GetResult(data);
    case Events::EventEnum::Scp079Recontaining:
        return Scp079Recontaining::GetResult(data);
    case Events::EventEnum::Scp079RoomBlackout:
        return Scp079RoomBlackout::GetResult(data);
    // Archived event resolver: Scp079TriggeringDoor -> Scp079TriggeringDoor::GetResult(data);
    case Events::EventEnum::Scp079ZoneBlackout:
        return Scp079ZoneBlackout::GetResult(data);
    case Events::EventEnum::Scp096AddingTarget:
        return Scp096AddingTarget::GetResult(data);
    // Archived event resolver: Scp096CalmingDown -> Scp096CalmingDown::GetResult(data);
    case Events::EventEnum::Scp096Charging:
        return Scp096Charging::GetResult(data);
    case Events::EventEnum::Scp096Enraging:
        return Scp096Enraging::GetResult(data);
    // Archived event resolver: Scp096RemovingTarget -> Scp096RemovingTarget::GetResult(data);
    // Archived event resolver: Scp096StartPryingGate -> Scp096StartPryingGate::GetResult(data);
    // Archived event resolver: Scp096TryingNotToCry -> Scp096TryingNotToCry::GetResult(data);
    case Events::EventEnum::Scp106Attacking:
        return Scp106Attacking::GetResult(data);
    // Archived event resolver: Scp106ExitStalking -> Scp106ExitStalking::GetResult(data);
    // Archived event resolver: Scp106Stalking -> Scp106Stalking::GetResult(data);
    case Events::EventEnum::Scp106Teleporting:
        return Scp106Teleporting::GetResult(data);
    // Archived event resolver: Scp127GainedExperience -> Scp127GainedExperience::GetResult(data);
    // Archived event resolver: Scp127GainingExperience -> Scp127GainingExperience::GetResult(data);
    // Archived event resolver: Scp127Talked -> Scp127Talked::GetResult(data);
    // Archived event resolver: Scp127Talking -> Scp127Talking::GetResult(data);
    // Archived event resolver: Scp1344ChangedStatus -> Scp1344ChangedStatus::GetResult(data);
    // Archived event resolver: Scp1344ChangingStatus -> Scp1344ChangingStatus::GetResult(data);
    // Archived event resolver: Scp1344Deactivated -> Scp1344Deactivated::GetResult(data);
    // Archived event resolver: Scp1344Deactivating -> Scp1344Deactivating::GetResult(data);
    // Archived event resolver: Scp1344TryingDeactivating -> Scp1344TryingDeactivating::GetResult(data);
    // Archived event resolver: Scp1507AttackingDoor -> Scp1507AttackingDoor::GetResult(data);
    // Archived event resolver: Scp1507Screaming -> Scp1507Screaming::GetResult(data);
    // Archived event resolver: Scp1507SpawningFlamingos -> Scp1507SpawningFlamingos::GetResult(data);
    // Archived event resolver: Scp1507UsingTape -> Scp1507UsingTape::GetResult(data);
    // Archived event resolver: Scp1509Resurrecting -> Scp1509Resurrecting::GetResult(data);
    // Archived event resolver: Scp1509TriggeringAttack -> Scp1509TriggeringAttack::GetResult(data);
    // Archived event resolver: Scp173AddingObserver -> Scp173AddingObserver::GetResult(data);
    // Archived event resolver: Scp173BeingObserved -> Scp173BeingObserved::GetResult(data);
    // Archived event resolver: Scp173Blinking -> Scp173Blinking::GetResult(data);
    // Archived event resolver: Scp173BlinkingRequest -> Scp173BlinkingRequest::GetResult(data);
    case Events::EventEnum::Scp173PlacingTantrum:
        return Scp173PlacingTantrum::GetResult(data);
    // Archived event resolver: Scp173RemovedObserver -> Scp173RemovedObserver::GetResult(data);
    // Archived event resolver: Scp173UsingBreakneckSpeeds -> Scp173UsingBreakneckSpeeds::GetResult(data);
    case Events::EventEnum::Scp244DamagingScp244:
        return Scp244DamagingScp244::GetResult(data);
    case Events::EventEnum::Scp244OpeningScp244:
        return Scp244OpeningScp244::GetResult(data);
    // Archived event resolver: Scp244UsingScp244 -> Scp244UsingScp244::GetResult(data);
    // Archived event resolver: Scp2536FindingPosition -> Scp2536FindingPosition::GetResult(data);
    // Archived event resolver: Scp2536FoundPosition -> Scp2536FoundPosition::GetResult(data);
    case Events::EventEnum::Scp2536GrantingGift:
        return Scp2536GrantingGift::GetResult(data);
    // Archived event resolver: Scp2536OpeningGift -> Scp2536OpeningGift::GetResult(data);
    // Archived event resolver: Scp3114Dancing -> Scp3114Dancing::GetResult(data);
    // Archived event resolver: Scp3114Disguised -> Scp3114Disguised::GetResult(data);
    // Archived event resolver: Scp3114Disguising -> Scp3114Disguising::GetResult(data);
    // Archived event resolver: Scp3114Revealed -> Scp3114Revealed::GetResult(data);
    // Archived event resolver: Scp3114Revealing -> Scp3114Revealing::GetResult(data);
    // Archived event resolver: Scp3114Slapped -> Scp3114Slapped::GetResult(data);
    case Events::EventEnum::Scp3114Strangling:
        return Scp3114Strangling::GetResult(data);
    // Archived event resolver: Scp3114TryUseBody -> Scp3114TryUseBody::GetResult(data);
    // Archived event resolver: Scp3114VoiceLines -> Scp3114VoiceLines::GetResult(data);
    // Archived event resolver: Scp330DroppingScp330 -> Scp330DroppingScp330::GetResult(data);
    // Archived event resolver: Scp330EatenScp330 -> Scp330EatenScp330::GetResult(data);
    // Archived event resolver: Scp330EatingScp330 -> Scp330EatingScp330::GetResult(data);
    // Archived event resolver: Scp330InteractingScp330 -> Scp330InteractingScp330::GetResult(data);
    // Archived event resolver: Scp559Interacting -> Scp559Interacting::GetResult(data);
    // Archived event resolver: Scp559Spawning -> Scp559Spawning::GetResult(data);
    // Archived event resolver: Scp914Activating -> Scp914Activating::GetResult(data);
    // Archived event resolver: Scp914ChangingKnobSetting -> Scp914ChangingKnobSetting::GetResult(data);
    // Archived event resolver: Scp914UpgradedInventoryItem -> Scp914UpgradedInventoryItem::GetResult(data);
    // Archived event resolver: Scp914UpgradedPickup -> Scp914UpgradedPickup::GetResult(data);
    // Archived event resolver: Scp914UpgradingInventoryItem -> Scp914UpgradingInventoryItem::GetResult(data);
    // Archived event resolver: Scp914UpgradingPickup -> Scp914UpgradingPickup::GetResult(data);
    case Events::EventEnum::Scp914UpgradingPlayer:
        return Scp914UpgradingPlayer::GetResult(data);
    // Archived event resolver: Scp939ChangingFocus -> Scp939ChangingFocus::GetResult(data);
    case Events::EventEnum::Scp939Clawed:
        return Scp939Clawed::GetResult(data);
    case Events::EventEnum::Scp939Lunging:
        return Scp939Lunging::GetResult(data);
    // Archived event resolver: Scp939PlacedAmnesticCloud -> Scp939PlacedAmnesticCloud::GetResult(data);
    case Events::EventEnum::Scp939PlacingAmnesticCloud:
        return Scp939PlacingAmnesticCloud::GetResult(data);
    // Archived event resolver: Scp939PlacingMimicPoint -> Scp939PlacingMimicPoint::GetResult(data);
    // Archived event resolver: Scp939PlayingFootstep -> Scp939PlayingFootstep::GetResult(data);
    // Archived event resolver: Scp939PlayingSound -> Scp939PlayingSound::GetResult(data);
    // Archived event resolver: Scp939PlayingVoice -> Scp939PlayingVoice::GetResult(data);
    // Archived event resolver: Scp939SavingVoice -> Scp939SavingVoice::GetResult(data);
    // Archived event resolver: Scp939UpdatedCloudState -> Scp939UpdatedCloudState::GetResult(data);
    // Archived event resolver: Scp939ValidatingVisibility -> Scp939ValidatingVisibility::GetResult(data);
    // Archived event resolver: ServerAddingUnitName -> ServerAddingUnitName::GetResult(data);
    // Archived event resolver: ServerAllPlayersSpawned -> ServerAllPlayersSpawned::GetResult(data);
    // Archived event resolver: ServerChoosingStartTeamQueue -> ServerChoosingStartTeamQueue::GetResult(data);
    case Events::EventEnum::ServerCompletingObjective:
        return ServerCompletingObjective::GetResult(data);
    case Events::EventEnum::ServerEndingRound:
        return ServerEndingRound::GetResult(data);
    // Archived event resolver: ServerLocalReporting -> ServerLocalReporting::GetResult(data);
    // Archived event resolver: ServerReloadedConfigs -> ServerReloadedConfigs::GetResult(data);
    // Archived event resolver: ServerReloadedGameplay -> ServerReloadedGameplay::GetResult(data);
    // Archived event resolver: ServerReloadedPermissions -> ServerReloadedPermissions::GetResult(data);
    // Archived event resolver: ServerReloadedPlugins -> ServerReloadedPlugins::GetResult(data);
    // Archived event resolver: ServerReloadedRA -> ServerReloadedRA::GetResult(data);
    // Archived event resolver: ServerReloadedTranslations -> ServerReloadedTranslations::GetResult(data);
    case Events::EventEnum::ServerReportingCheater:
        return ServerReportingCheater::GetResult(data);
    case Events::EventEnum::ServerRespawnedTeam:
        return ServerRespawnedTeam::GetResult(data);
    // Archived event resolver: ServerRespawningTeam -> ServerRespawningTeam::GetResult(data);
    // Archived event resolver: ServerSelectingRespawnTeam -> ServerSelectingRespawnTeam::GetResult(data);
    // Archived event resolver: ServerUnbanned -> ServerUnbanned::GetResult(data);
    // Archived event resolver: ServerUnbanning -> ServerUnbanning::GetResult(data);
    // Archived event resolver: ServerWaitingForPlayers -> ServerWaitingForPlayers::GetResult(data);
    // Archived event resolver: WarheadChangingLeverStatus -> WarheadChangingLeverStatus::GetResult(data);
    case Events::EventEnum::WarheadDeadmanSwitchInitiating:
        return WarheadDeadmanSwitchInitiating::GetResult(data);
    case Events::EventEnum::WarheadDetonated:
        return WarheadDetonated::GetResult(data);
    case Events::EventEnum::WarheadDetonating:
        return WarheadDetonating::GetResult(data);
    case Events::EventEnum::WarheadStarting:
        return WarheadStarting::GetResult(data);
    case Events::EventEnum::WarheadStopping:
        return WarheadStopping::GetResult(data);
    case Events::EventEnum::FlashGrenadeThrown:
        return FlashGrenadeThrown::GetResult(data);
    case Events::EventEnum::FlashGrenadeExploded:
        return FlashGrenadeExploded::GetResult(data);
    case Events::EventEnum::SCP268Used:
        return SCP268Used::GetResult(data);
    case Events::EventEnum::SCP268Expired:
        return SCP268Expired::GetResult(data);
    default:
        return Invalid::GetResult(Events::EventToString(event));
    }

    return Invalid::GetResult("Unknown");
}

Packet::Reader::Reader(const std::vector<uint8_t> &data)
{
    m_Data = const_cast<std::vector<uint8_t> *>(&data);
}

bool Packet::Reader::HasRemaining(size_t bytes) const
{
    return m_Data != nullptr && m_Offset >= 0 && static_cast<size_t>(m_Offset) + bytes <= m_Data->size();
}

std::string Packet::Reader::ReadDotNetString()
{
    uint32_t length = 0;
    uint32_t shift = 0;

    while (true)
    {
        if (m_Offset >= m_Data->size())
        {
            std::println("[Packet::ReadDotNetString] Unexpected end of data");
            break;
        }

        uint8_t byte = (*m_Data)[m_Offset++];

        length |= static_cast<uint32_t>(byte & 0x7F) << shift;

        if ((byte & 0x80) == 0)
            break;

        shift += 7;

        if (shift >= 32)
        {
            std::println("[Packet::ReadDotNetString] Invalid .NET string length");
            break;
        }
    }

    if (m_Offset + length > m_Data->size())
    {
        std::println("[Packet::ReadDotNetString] String exceeds buffer");
        return "";
    }

    std::string result(
        reinterpret_cast<const char *>(m_Data->data() + m_Offset),
        length);

    m_Offset += length;

    return result;
}

std::vector<uint8_t> Packet::Reader::ReadBytes(int size)
{
    if (size < 0 || !HasRemaining(static_cast<size_t>(size)))
    {
        if (size < 0)
            std::println("[Packet::Reader::ReadBytes] Negative length requested: {}", size);
        else
            std::println("[Packet::Reader::ReadBytes] Requested {} bytes but only {} remain", size, std::max(0, static_cast<int>(m_Data->size() - m_Offset)));
        return {};
    }

    std::vector<uint8_t> data(size);
    std::memcpy(data.data(), m_Data->data() + m_Offset, size);
    m_Offset += size;
    return data;
}
