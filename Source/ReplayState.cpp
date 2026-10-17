#include "ReplayState.hpp"
#include <print>
#include "Rooms.hpp"

namespace
{
    template <typename PacketData>
    void HandleExplicitEvent(const PacketData &data, Replay::State &state, bool playedInReverse, Events::EventEnum event)
    {
        if (playedInReverse || state.Paused)
            return;

        Events::Point point{};
        point.Event = event;
        point.Tick = state.CurrentReadTick;

        if (data.HasPlayerId)
        {
            if (auto playerIt = state.Players.find(data.PlayerId); playerIt != state.Players.end())
            {
                point.Position = playerIt->second.Position;
                point.GiverRole = playerIt->second.Role;
                point.GiverNickname = playerIt->second.Nickname;
            }
        }

        state.Points.push_back(point);
    }
}


void Replay::HandlePacket(const Packet::Invalid::Data &data, State &state, bool playedInReverse)
{
    std::println("[Replay::HandlePacket][Invalid] Unimplemented packet {}", data.Name);
}

void Replay::HandlePacket(const Packet::NewTick::Data &data, State &state, bool playedInReverse)
{
}

void Replay::HandlePacket(const Packet::Room::Data &data, State &state, bool playedInReverse)
{
    state.RoomPositions.push_back({data.Name, Vector3(data.PositionX, data.PositionY, data.PositionZ), Quaternion(data.RotationX, data.RotationY, data.RotationZ, data.RotationW)});
}

void Replay::HandlePacket(const Packet::PlayerJoined::Data &data, State &state, bool playedInReverse)
{
    if (!playedInReverse)
    {
        Player::Data playerData = {};
        playerData.Nickname = data.Nickname;
        playerData.Role = (Events::RoleTypeId)data.Role;

        state.Players.insert({data.PlayerId, playerData});

        Events::Point point{};
        point.Event = Events::EventEnum::PlayerJoined;
        point.Tick = state.CurrentReadTick;
        point.GiverRole = playerData.Role;
        point.GiverNickname = playerData.Nickname;
        state.Points.push_back(point);
    }
    else
    {
        state.Players.erase(data.PlayerId);
    }
}

void Replay::HandlePacket(const Packet::PlayerLeft::Data &data, State &state, bool playedInReverse)
{
    if (!playedInReverse)
    {
        auto it = state.Players.find(data.PlayerId);
        if (it == state.Players.end())
            return;

        Player::Data playerData = it->second;
        state.PlayerHistory.Save(data.PlayerId, state.CurrentReadTick, playerData);

        Events::Point point{};
        point.Event = Events::EventEnum::PlayerLeft;
        point.Tick = state.CurrentReadTick;
        point.Position = playerData.Position;
        point.GiverRole = playerData.Role;
        point.GiverNickname = playerData.Nickname;
        state.Points.push_back(point);

        state.Players.erase(data.PlayerId);
    }
    else
    {
        auto savedPlayer = state.PlayerHistory.Get(data.PlayerId, state.CurrentReadTick);
        if (!savedPlayer)
            return;

        state.Players.insert({data.PlayerId, *savedPlayer});
    }
}

void Replay::HandlePacket(const Packet::PlayerPosition::Data &data, State &state, bool playedInReverse)
{
    if (auto it = state.Players.find(data.PlayerId); it != state.Players.end())
    {
        it->second.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
        it->second.Rotation = Quaternion(data.RotationX, data.RotationY, data.RotationZ, data.RotationW);

        if (state.Paused)
        {
            return;
        }

        auto &lastTime = state.LastTimePositionPointPlacedMap[data.PlayerId];
        if (lastTime > 32)
        {
            Events::Point point{};
            point.Event = Events::EventEnum::PlayerPosition;
            point.Tick = state.CurrentReadTick;
            point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
            point.GiverRole = it->second.Role;
            state.Points.push_back(point);
            lastTime = 0;
        }

        lastTime++;
    }
}

void Replay::HandlePacket(const Packet::PlayerChangedRoles::Data &data, State &state, bool playedInReverse)
{
    auto it = state.Players.find(data.PlayerId);
    if (it == state.Players.end())
        return;

    const auto playerId = it->first;
    const auto tick = static_cast<int>(state.CurrentReadTick);

    if (playedInReverse)
    {
        auto previousRole = state.RoleHistory.Get(playerId, tick);
        if (!previousRole)
            return;
        it->second.Role = *previousRole;
        return;
    }

    const auto newRole = static_cast<Events::RoleTypeId>(data.Role);
    state.RoleHistory.Save(playerId, tick, it->second.Role);
    it->second.Role = newRole;
}

void Replay::HandlePacket(const Packet::DoorOpened::Data &data, State &state, bool playedInReverse)
{
    if (auto it = state.Players.find(data.PlayerId); it != state.Players.end())
    {
        if (state.Paused)
            return;
        Events::Point point{};
        point.Event = Events::EventEnum::DoorOpened;
        point.Tick = state.CurrentReadTick;
        point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
        point.GiverRole = it->second.Role;
        state.Points.push_back(point);
    }
}

void Replay::HandlePacket(const Packet::DoorClosed::Data &data, State &state, bool playedInReverse)
{
    if (auto it = state.Players.find(data.PlayerId); it != state.Players.end())
    {
        if (state.Paused)
            return;
        Events::Point point{};
        point.Event = Events::EventEnum::DoorClosed;
        point.Tick = state.CurrentReadTick;
        point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
        point.GiverRole = it->second.Role;
        state.Points.push_back(point);
    }
}

void Replay::HandlePacket(const Packet::PlayerDied::Data &data, State &state, bool playedInReverse)
{
    if (auto victimIt = state.Players.find(data.VictimId); victimIt != state.Players.end())
    {
        if (playedInReverse || state.Paused)
        {
            return;
        }
        Events::Point point{};
        point.Event = Events::EventEnum::PlayerDied;
        point.Tick = state.CurrentReadTick;
        point.Position = victimIt->second.Position;
        point.DmgType = (Damage::Type)data.DamageType;

        auto attackerIt = state.Players.find(data.AttackerId);
        point.GiverRole = attackerIt != state.Players.end() ? attackerIt->second.Role : Events::RoleTypeId::None;
        point.GiverNickname = attackerIt != state.Players.end() ? attackerIt->second.Nickname : "";
        point.ReceiverRole = victimIt->second.Role;
        point.ReceiverNickname = victimIt->second.Nickname;
        state.Points.push_back(point);
    }
}

void Replay::HandlePacket(const Packet::CancelChargingMicroHid::Data &data, State &state, bool playedInReverse)
{
    if (auto playerIt = state.Players.find(data.PlayerId); playerIt != state.Players.end())
    {
        if (playedInReverse || state.Paused)
        {
            return;
        }

        Events::Point point{};
        point.Event = Events::EventEnum::MicroHidCanceledCharging;
        point.GiverNickname = playerIt->second.Nickname;
        point.GiverRole = playerIt->second.Role;
        point.Position = playerIt->second.Position;
        point.Tick = state.CurrentReadTick;
        state.Points.push_back(point);
    }
}

void Replay::HandlePacket(const Packet::ChargingMicroHid::Data &data, State &state, bool playedInReverse)
{
    if (auto playerIt = state.Players.find(data.PlayerId); playerIt != state.Players.end())
    {
        if (playedInReverse || state.Paused)
        {
            return;
        }

        Events::Point point{};
        point.Event = Events::EventEnum::MicroHidCharging;
        point.GiverNickname = playerIt->second.Nickname;
        point.GiverRole = playerIt->second.Role;
        point.Position = playerIt->second.Position;
        point.Tick = state.CurrentReadTick;
        state.Points.push_back(point);
    }
}

void Replay::HandlePacket(const Packet::FiringMicroHid::Data &data, State &state, bool playedInReverse)
{
    if (auto playerIt = state.Players.find(data.PlayerId); playerIt != state.Players.end())
    {
        if (playedInReverse || state.Paused)
        {
            return;
        }

        Events::Point point{};
        point.Event = Events::EventEnum::MicroHidFiring;
        point.GiverNickname = playerIt->second.Nickname;
        point.GiverRole = playerIt->second.Role;
        point.Position = playerIt->second.Position;
        point.Tick = state.CurrentReadTick;
        state.Points.push_back(point);
    }
}

void Replay::HandlePacket(const Packet::PlayerEscaped::Data &data, State &state, bool playedInReverse)
{
    if (auto playerIt = state.Players.find(data.PlayerId); playerIt != state.Players.end())
    {
        if (playedInReverse || state.Paused)
        {
            return;
        }

        Events::Point point{};
        point.Event = Events::EventEnum::PlayerEscaped;
        point.ReceiverNickname = playerIt->second.Nickname;
        point.ReceiverRole = playerIt->second.Role;
        point.Position = playerIt->second.Position;
        point.Tick = state.CurrentReadTick;
        state.Points.push_back(point);
    }
}

void Replay::HandlePacket(const Packet::PlayerEscorted::Data &data, State &state, bool playedInReverse)
{
    if (auto escorteeIt = state.Players.find(data.PlayerId); escorteeIt != state.Players.end())
    {
        if (playedInReverse || state.Paused)
        {
            return;
        }
        Events::Point point{};
        point.Event = Events::EventEnum::PlayerEscorted;
        point.Tick = state.CurrentReadTick;
        point.Position = escorteeIt->second.Position;

        auto cufferIt = state.Players.find(data.CufferId);
        point.GiverRole = cufferIt != state.Players.end() ? cufferIt->second.Role : Events::RoleTypeId::None;
        point.GiverNickname = cufferIt != state.Players.end() ? cufferIt->second.Nickname : "";
        point.ReceiverRole = escorteeIt->second.Role;
        point.ReceiverNickname = escorteeIt->second.Nickname;
        state.Points.push_back(point);
    }
}

void Replay::HandlePacket(const Packet::VersionPacket::Data &data, State &state, bool playedInReverse)
{
}

void Replay::HandlePacket(const Packet::NtfWave::Data &data, State &state, bool playedInReverse)
{
    if (playedInReverse || state.Paused)
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::NtfWave;
    point.Tick = state.CurrentReadTick;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::NtfMiniWave::Data &data, State &state, bool playedInReverse)
{
    if (playedInReverse || state.Paused)
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::NtfMiniWave;
    point.Tick = state.CurrentReadTick;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::CIWave::Data &data, State &state, bool playedInReverse)
{
    if (playedInReverse || state.Paused)
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::CIWave;
    point.Tick = state.CurrentReadTick;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::CIMiniWave::Data &data, State &state, bool playedInReverse)
{
    if (playedInReverse || state.Paused)
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::CIMiniWave;
    point.Tick = state.CurrentReadTick;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::BallThrown::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::BallThrown;
    point.Tick = state.CurrentReadTick;
    point.Position = playerIt->second.Position;
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::HitByBall::Data &data, State &state, bool playedInReverse)
{
    auto victimIt = state.Players.find(data.VictimId);
    if (playedInReverse || state.Paused || victimIt == state.Players.end())
        return;

    auto attackerIt = state.Players.find(data.AttackerId);
    Events::Point point{};
    point.Event = Events::EventEnum::HitByBall;
    point.Tick = state.CurrentReadTick;
    point.Position = victimIt->second.Position;
    point.GiverRole = attackerIt != state.Players.end() ? attackerIt->second.Role : Events::RoleTypeId::None;
    point.GiverNickname = attackerIt != state.Players.end() ? attackerIt->second.Nickname : "";
    point.ReceiverRole = victimIt->second.Role;
    point.ReceiverNickname = victimIt->second.Nickname;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::GrenadeThrown::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::GrenadeThrown;
    point.Tick = state.CurrentReadTick;
    point.Position = playerIt->second.Position;
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::GrenadeExploded::Data &data, State &state, bool playedInReverse)
{
    if (playedInReverse || state.Paused)
        return;

    auto playerIt = state.Players.find(data.PlayerId);
    Events::Point point{};
    point.Event = Events::EventEnum::GrenadeExploded;
    point.Tick = state.CurrentReadTick;
    point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
    if (playerIt != state.Players.end())
    {
        point.GiverRole = playerIt->second.Role;
        point.GiverNickname = playerIt->second.Nickname;
        point.ReceiverRole = playerIt->second.Role;
    }
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::PickingUpItem::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::PickingUpItem;
    point.Tick = state.CurrentReadTick;
    point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    point.CustomData = data.ItemId;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::DroppedItem::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::DroppedItem;
    point.Tick = state.CurrentReadTick;
    point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    point.CustomData = data.ItemId;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::PlayerHurt::Data &data, State &state, bool playedInReverse)
{
    auto victimIt = state.Players.find(data.VictimId);
    if (playedInReverse || state.Paused || victimIt == state.Players.end())
        return;

    auto attackerIt = state.Players.find(data.AttackerId);
    Events::Point point{};
    point.Event = Events::EventEnum::PlayerHurt;
    point.Tick = state.CurrentReadTick;
    point.Position = victimIt->second.Position;
    point.ReceiverRole = victimIt->second.Role;
    point.ReceiverNickname = victimIt->second.Nickname;
    point.GiverRole = attackerIt != state.Players.end() ? attackerIt->second.Role : Events::RoleTypeId::None;
    point.GiverNickname = attackerIt != state.Players.end() ? attackerIt->second.Nickname : "";
    point.CustomData = data.DamageInfo;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::PlayerShot::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::PlayerShot;
    point.Tick = state.CurrentReadTick;
    point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
    point.Rotation = playerIt->second.Rotation;
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    point.CustomData = data.Weapon;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::ItemUsed::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::ItemUsed;
    point.Tick = state.CurrentReadTick;
    point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    point.CustomData = data.Item;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::PlayerAction::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = data.Event;
    point.Tick = state.CurrentReadTick;
    point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;

    if (data.TargetId != 0)
    {
        if (auto targetIt = state.Players.find(data.TargetId); targetIt != state.Players.end())
        {
            point.ReceiverRole = targetIt->second.Role;
            point.ReceiverNickname = targetIt->second.Nickname;
        }
    }

    state.Points.push_back(point);
}


void Replay::HandlePacket(const Packet::FlashGrenadeThrown::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::FlashGrenadeThrown;
    point.Tick = state.CurrentReadTick;
    point.Position = playerIt->second.Position;
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::FlashGrenadeExploded::Data &data, State &state, bool playedInReverse)
{
    if (playedInReverse || state.Paused)
        return;

    auto playerIt = state.Players.find(data.PlayerId);
    Events::Point point{};
    point.Event = Events::EventEnum::FlashGrenadeExploded;
    point.Tick = state.CurrentReadTick;
    point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);
    if (playerIt != state.Players.end())
    {
        point.GiverRole = playerIt->second.Role;
        point.GiverNickname = playerIt->second.Nickname;
        point.ReceiverRole = playerIt->second.Role;
    }
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::SCP268Used::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::SCP268Used;
    point.Tick = state.CurrentReadTick;
    point.Position = playerIt->second.Position;
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    state.Points.push_back(point);
}

void Replay::HandlePacket(const Packet::SCP268Expired::Data &data, State &state, bool playedInReverse)
{
    auto playerIt = state.Players.find(data.PlayerId);
    if (playedInReverse || state.Paused || playerIt == state.Players.end())
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::SCP268Expired;
    point.Tick = state.CurrentReadTick;
    point.Position = playerIt->second.Position;
    point.GiverRole = playerIt->second.Role;
    point.GiverNickname = playerIt->second.Nickname;
    state.Points.push_back(point);
}
void Replay::HandlePacket(const Packet::CassieSendingCassieMessage::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::CassieSendingCassieMessage);
}

#if 0
void Replay::HandlePacket(const Packet::ItemCackling::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemCackling);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemChangingAmmo::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemChangingAmmo);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemChangingAttachments::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemChangingAttachments);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemChangingMicroHIDPickupState::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemChangingMicroHIDPickupState);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemChargingJailbird::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemChargingJailbird);
}

#endif
void Replay::HandlePacket(const Packet::ItemDisruptorFiring::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemDisruptorFiring);
}

#if 0
void Replay::HandlePacket(const Packet::ItemInspectedItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemInspectedItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemInspectingItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemInspectingItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemJailbirdChangedWearState::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemJailbirdChangedWearState);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemJailbirdChangingWearState::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemJailbirdChangingWearState);
}

#endif
void Replay::HandlePacket(const Packet::ItemJailbirdChargeComplete::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemJailbirdChargeComplete);
}

#if 0
void Replay::HandlePacket(const Packet::ItemKeycardInteracting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemKeycardInteracting);
}

#endif
void Replay::HandlePacket(const Packet::ItemPunching::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemPunching);
}

#if 0
void Replay::HandlePacket(const Packet::ItemReceivingPreference::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemReceivingPreference);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemSwinging::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemSwinging);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ItemUsingRadioPickupBattery::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ItemUsingRadioPickupBattery);
}

#endif
void Replay::HandlePacket(const Packet::MapAnnouncingDecontamination::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapAnnouncingDecontamination);
}

void Replay::HandlePacket(const Packet::MapAnnouncingScpTermination::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapAnnouncingScpTermination);
}

#if 0
void Replay::HandlePacket(const Packet::MapChangedIntoGrenade::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapChangedIntoGrenade);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapChangingIntoGrenade::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapChangingIntoGrenade);
}

#endif
void Replay::HandlePacket(const Packet::MapDecontaminating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapDecontaminating);
}

#if 0
void Replay::HandlePacket(const Packet::MapElevatorSequencesUpdated::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapElevatorSequencesUpdated);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapFillingLocker::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapFillingLocker);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapGenerated::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapGenerated);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapGenerating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapGenerating);
}

#endif
void Replay::HandlePacket(const Packet::MapGeneratorActivating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapGeneratorActivating);
}

#if 0
void Replay::HandlePacket(const Packet::MapPickupAdded::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapPickupAdded);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapPickupDestroyed::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapPickupDestroyed);
}

#endif
void Replay::HandlePacket(const Packet::MapPlacingBulletHole::Data &data, State &state, bool playedInReverse)
{
    if (playedInReverse || state.Paused)
        return;

    Events::Point point{};
    point.Event = Events::EventEnum::MapPlacingBulletHole;
    point.Tick = state.CurrentReadTick;
    if (data.HasPosition)
        point.Position = Vector3(data.PositionX, data.PositionY, data.PositionZ);

    if (data.HasPlayerId)
    {
        if (auto playerIt = state.Players.find(data.PlayerId); playerIt != state.Players.end())
        {
            if (!data.HasPosition)
                point.Position = playerIt->second.Position;
            point.GiverRole = playerIt->second.Role;
            point.GiverNickname = playerIt->second.Nickname;
        }
    }

    state.Points.push_back(point);
}

#if 0
void Replay::HandlePacket(const Packet::MapPlacingPickupIntoPocketDimension::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapPlacingPickupIntoPocketDimension);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapScp244Spawning::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapScp244Spawning);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapSpawningGrenadeEffect::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapSpawningGrenadeEffect);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapSpawningItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapSpawningItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapSpawningRoomConnector::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapSpawningRoomConnector);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapSpawningTeamVehicle::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapSpawningTeamVehicle);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::MapTurningOffLights::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::MapTurningOffLights);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerActivatingWorkstation::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerActivatingWorkstation);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerAimingDownSight::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerAimingDownSight);
}

#endif
void Replay::HandlePacket(const Packet::PlayerBanned::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerBanned);
}

#if 0
void Replay::HandlePacket(const Packet::PlayerBanning::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerBanning);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerCancelledItemUse::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerCancelledItemUse);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerCancellingItemUse::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerCancellingItemUse);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangedEmotion::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangedEmotion);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangedItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangedItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangedRatio::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangedRatio);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingDangerState::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingDangerState);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingDisruptorMode::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingDisruptorMode);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingEmotion::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingEmotion);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingGroup::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingGroup);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingMoveState::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingMoveState);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingNickname::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingNickname);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingRadioPreset::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingRadioPreset);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerChangingSpectatedPlayer::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerChangingSpectatedPlayer);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerClosingGenerator::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerClosingGenerator);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerConsumingItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerConsumingItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDamagingDoor::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDamagingDoor);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDamagingShootingTarget::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDamagingShootingTarget);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDamagingWindow::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDamagingWindow);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDeactivatingWorkstation::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDeactivatingWorkstation);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDestroying::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDestroying);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDrinkingCoffee::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDrinkingCoffee);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDroppedAmmo::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDroppedAmmo);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDroppingAmmo::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDroppingAmmo);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDroppingItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDroppingItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDroppingNothing::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDroppingNothing);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerDryfiringWeapon::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerDryfiringWeapon);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerEarningAchievement::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerEarningAchievement);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerEnteringEnvironmentalHazard::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerEnteringEnvironmentalHazard);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerEnteringKillerCollision::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerEnteringKillerCollision);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerExitingEnvironmentalHazard::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerExitingEnvironmentalHazard);
}

#endif
void Replay::HandlePacket(const Packet::PlayerExplodingMicroHID::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerExplodingMicroHID);
}

#if 0
void Replay::HandlePacket(const Packet::PlayerFailingEscapePocketDimension::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerFailingEscapePocketDimension);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerFlippingCoin::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerFlippingCoin);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerHealed::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerHealed);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerHealing::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerHealing);
}

#endif
void Replay::HandlePacket(const Packet::PlayerHit::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerHit);
}

#if 0
void Replay::HandlePacket(const Packet::PlayerInteracted::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerInteracted);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerInteractingLocker::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerInteractingLocker);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerInteractingShootingTarget::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerInteractingShootingTarget);
}

#endif
void Replay::HandlePacket(const Packet::PlayerIntercomSpeaking::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerIntercomSpeaking);
}

#if 0
void Replay::HandlePacket(const Packet::PlayerIssuingMute::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerIssuingMute);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerItemAdded::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerItemAdded);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerItemRemoved::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerItemRemoved);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerJumping::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerJumping);
}

#endif
void Replay::HandlePacket(const Packet::PlayerKicked::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerKicked);
}

void Replay::HandlePacket(const Packet::PlayerKicking::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerKicking);
}

#if 0
void Replay::HandlePacket(const Packet::PlayerLanding::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerLanding);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerMakingNoise::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerMakingNoise);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerMicroHIDOpeningDoor::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerMicroHIDOpeningDoor);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerOpeningGenerator::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerOpeningGenerator);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerPlayingAudioLog::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerPlayingAudioLog);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerPreAuthenticating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerPreAuthenticating);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerReceivingEffect::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerReceivingEffect);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerReceivingGunSound::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerReceivingGunSound);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerReceivingVoiceMessage::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerReceivingVoiceMessage);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerReloadedWeapon::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerReloadedWeapon);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerReloadingWeapon::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerReloadingWeapon);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerRemovedHandcuffs::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerRemovedHandcuffs);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerRemovingHandcuffs::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerRemovingHandcuffs);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerReservedSlot::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerReservedSlot);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerRevokingMute::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerRevokingMute);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerRoomChanged::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerRoomChanged);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerRotatingRevolver::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerRotatingRevolver);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSavingByAntiScp207::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSavingByAntiScp207);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerScp1576TransmissionEnded::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerScp1576TransmissionEnded);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSearchingPickup::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSearchingPickup);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSendingAdminChatMessage::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSendingAdminChatMessage);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSendingGunSound::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSendingGunSound);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSendingValidCommand::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSendingValidCommand);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSentValidCommand::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSentValidCommand);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSpawned::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSpawned);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSpawnedRagdoll::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSpawnedRagdoll);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSpawning::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSpawning);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerSpawningRagdoll::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerSpawningRagdoll);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerStayingOnEnvironmentalHazard::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerStayingOnEnvironmentalHazard);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerStoppingGenerator::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerStoppingGenerator);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerThrowingRequest::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerThrowingRequest);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerTogglingFlashlight::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerTogglingFlashlight);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerTogglingNoClip::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerTogglingNoClip);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerTogglingOverwatch::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerTogglingOverwatch);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerTogglingRadio::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerTogglingRadio);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerTogglingWeaponFlashlight::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerTogglingWeaponFlashlight);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerTransmitting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerTransmitting);
}

#endif
void Replay::HandlePacket(const Packet::PlayerTriggeringTesla::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerTriggeringTesla);
}

#if 0
void Replay::HandlePacket(const Packet::PlayerUnloadedWeapon::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerUnloadedWeapon);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerUnloadingWeapon::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerUnloadingWeapon);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerUnlockingGenerator::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerUnlockingGenerator);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerUsingItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerUsingItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerUsingItemCompleted::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerUsingItemCompleted);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerUsingMicroHIDEnergy::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerUsingMicroHIDEnergy);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerUsingRadioBattery::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerUsingRadioBattery);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerVoiceChatting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerVoiceChatting);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::PlayerZoneChanged::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::PlayerZoneChanged);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp049ActivatingSense::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp049ActivatingSense);
}

#endif
void Replay::HandlePacket(const Packet::Scp049Attacking::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp049Attacking);
}

void Replay::HandlePacket(const Packet::Scp049FinishingRecall::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp049FinishingRecall);
}

#if 0
void Replay::HandlePacket(const Packet::Scp049FinishingSense::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp049FinishingSense);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp049SendingCall::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp049SendingCall);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp049StartingRecall::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp049StartingRecall);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp0492ConsumedCorpse::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp0492ConsumedCorpse);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp0492ConsumingCorpse::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp0492ConsumingCorpse);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp0492TriggeringBloodlust::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp0492TriggeringBloodlust);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079ChangingCamera::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079ChangingCamera);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079ChangingSpeakerStatus::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079ChangingSpeakerStatus);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079ElevatorTeleporting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079ElevatorTeleporting);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079GainingExperience::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079GainingExperience);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079GainingLevel::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079GainingLevel);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079InteractingTesla::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079InteractingTesla);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079LockingDown::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079LockingDown);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079LosingSignal::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079LosingSignal);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079LostSignal::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079LostSignal);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp079Pinging::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079Pinging);
}

#endif
void Replay::HandlePacket(const Packet::Scp079Recontained::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079Recontained);
}

void Replay::HandlePacket(const Packet::Scp079Recontaining::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079Recontaining);
}

void Replay::HandlePacket(const Packet::Scp079RoomBlackout::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079RoomBlackout);
}

#if 0
void Replay::HandlePacket(const Packet::Scp079TriggeringDoor::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079TriggeringDoor);
}

#endif
void Replay::HandlePacket(const Packet::Scp079ZoneBlackout::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp079ZoneBlackout);
}

void Replay::HandlePacket(const Packet::Scp096AddingTarget::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp096AddingTarget);
}

#if 0
void Replay::HandlePacket(const Packet::Scp096CalmingDown::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp096CalmingDown);
}

#endif
void Replay::HandlePacket(const Packet::Scp096Charging::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp096Charging);
}

void Replay::HandlePacket(const Packet::Scp096Enraging::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp096Enraging);
}

#if 0
void Replay::HandlePacket(const Packet::Scp096RemovingTarget::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp096RemovingTarget);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp096StartPryingGate::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp096StartPryingGate);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp096TryingNotToCry::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp096TryingNotToCry);
}

#endif
void Replay::HandlePacket(const Packet::Scp106Attacking::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp106Attacking);
}

#if 0
void Replay::HandlePacket(const Packet::Scp106ExitStalking::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp106ExitStalking);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp106Stalking::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp106Stalking);
}

#endif
void Replay::HandlePacket(const Packet::Scp106Teleporting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp106Teleporting);
}

#if 0
void Replay::HandlePacket(const Packet::Scp127GainedExperience::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp127GainedExperience);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp127GainingExperience::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp127GainingExperience);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp127Talked::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp127Talked);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp127Talking::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp127Talking);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1344ChangedStatus::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1344ChangedStatus);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1344ChangingStatus::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1344ChangingStatus);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1344Deactivated::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1344Deactivated);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1344Deactivating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1344Deactivating);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1344TryingDeactivating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1344TryingDeactivating);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1507AttackingDoor::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1507AttackingDoor);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1507Screaming::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1507Screaming);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1507SpawningFlamingos::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1507SpawningFlamingos);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1507UsingTape::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1507UsingTape);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1509Resurrecting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1509Resurrecting);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp1509TriggeringAttack::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp1509TriggeringAttack);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp173AddingObserver::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp173AddingObserver);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp173BeingObserved::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp173BeingObserved);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp173Blinking::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp173Blinking);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp173BlinkingRequest::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp173BlinkingRequest);
}

#endif
void Replay::HandlePacket(const Packet::Scp173PlacingTantrum::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp173PlacingTantrum);
}

#if 0
void Replay::HandlePacket(const Packet::Scp173RemovedObserver::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp173RemovedObserver);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp173UsingBreakneckSpeeds::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp173UsingBreakneckSpeeds);
}

#endif
void Replay::HandlePacket(const Packet::Scp244DamagingScp244::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp244DamagingScp244);
}

void Replay::HandlePacket(const Packet::Scp244OpeningScp244::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp244OpeningScp244);
}

#if 0
void Replay::HandlePacket(const Packet::Scp244UsingScp244::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp244UsingScp244);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp2536FindingPosition::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp2536FindingPosition);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp2536FoundPosition::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp2536FoundPosition);
}

#endif
void Replay::HandlePacket(const Packet::Scp2536GrantingGift::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp2536GrantingGift);
}

#if 0
void Replay::HandlePacket(const Packet::Scp2536OpeningGift::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp2536OpeningGift);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp3114Dancing::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114Dancing);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp3114Disguised::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114Disguised);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp3114Disguising::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114Disguising);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp3114Revealed::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114Revealed);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp3114Revealing::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114Revealing);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp3114Slapped::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114Slapped);
}

#endif
void Replay::HandlePacket(const Packet::Scp3114Strangling::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114Strangling);
}

#if 0
void Replay::HandlePacket(const Packet::Scp3114TryUseBody::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114TryUseBody);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp3114VoiceLines::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp3114VoiceLines);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp330DroppingScp330::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp330DroppingScp330);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp330EatenScp330::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp330EatenScp330);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp330EatingScp330::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp330EatingScp330);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp330InteractingScp330::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp330InteractingScp330);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp559Interacting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp559Interacting);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp559Spawning::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp559Spawning);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp914Activating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp914Activating);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp914ChangingKnobSetting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp914ChangingKnobSetting);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp914UpgradedInventoryItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp914UpgradedInventoryItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp914UpgradedPickup::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp914UpgradedPickup);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp914UpgradingInventoryItem::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp914UpgradingInventoryItem);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp914UpgradingPickup::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp914UpgradingPickup);
}

#endif
void Replay::HandlePacket(const Packet::Scp914UpgradingPlayer::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp914UpgradingPlayer);
}

#if 0
void Replay::HandlePacket(const Packet::Scp939ChangingFocus::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939ChangingFocus);
}

#endif
void Replay::HandlePacket(const Packet::Scp939Clawed::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939Clawed);
}

void Replay::HandlePacket(const Packet::Scp939Lunging::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939Lunging);
}

#if 0
void Replay::HandlePacket(const Packet::Scp939PlacedAmnesticCloud::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939PlacedAmnesticCloud);
}

#endif
void Replay::HandlePacket(const Packet::Scp939PlacingAmnesticCloud::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939PlacingAmnesticCloud);
}

#if 0
void Replay::HandlePacket(const Packet::Scp939PlacingMimicPoint::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939PlacingMimicPoint);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp939PlayingFootstep::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939PlayingFootstep);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp939PlayingSound::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939PlayingSound);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp939PlayingVoice::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939PlayingVoice);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp939SavingVoice::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939SavingVoice);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp939UpdatedCloudState::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939UpdatedCloudState);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::Scp939ValidatingVisibility::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::Scp939ValidatingVisibility);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerAddingUnitName::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerAddingUnitName);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerAllPlayersSpawned::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerAllPlayersSpawned);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerChoosingStartTeamQueue::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerChoosingStartTeamQueue);
}

#endif
void Replay::HandlePacket(const Packet::ServerCompletingObjective::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerCompletingObjective);
}

void Replay::HandlePacket(const Packet::ServerEndingRound::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerEndingRound);
}

#if 0
void Replay::HandlePacket(const Packet::ServerLocalReporting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerLocalReporting);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerReloadedConfigs::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerReloadedConfigs);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerReloadedGameplay::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerReloadedGameplay);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerReloadedPermissions::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerReloadedPermissions);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerReloadedPlugins::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerReloadedPlugins);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerReloadedRA::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerReloadedRA);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerReloadedTranslations::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerReloadedTranslations);
}

#endif
void Replay::HandlePacket(const Packet::ServerReportingCheater::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerReportingCheater);
}

void Replay::HandlePacket(const Packet::ServerRespawnedTeam::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerRespawnedTeam);
}

#if 0
void Replay::HandlePacket(const Packet::ServerRespawningTeam::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerRespawningTeam);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerSelectingRespawnTeam::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerSelectingRespawnTeam);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerUnbanned::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerUnbanned);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerUnbanning::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerUnbanning);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::ServerWaitingForPlayers::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::ServerWaitingForPlayers);
}

#endif
#if 0
void Replay::HandlePacket(const Packet::WarheadChangingLeverStatus::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::WarheadChangingLeverStatus);
}

#endif
void Replay::HandlePacket(const Packet::WarheadDeadmanSwitchInitiating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::WarheadDeadmanSwitchInitiating);
}

void Replay::HandlePacket(const Packet::WarheadDetonated::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::WarheadDetonated);
}

void Replay::HandlePacket(const Packet::WarheadDetonating::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::WarheadDetonating);
}

void Replay::HandlePacket(const Packet::WarheadStarting::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::WarheadStarting);
}

void Replay::HandlePacket(const Packet::WarheadStopping::Data &data, State &state, bool playedInReverse)
{
    HandleExplicitEvent(data, state, playedInReverse, Events::EventEnum::WarheadStopping);
}
