#include "ReplayState.hpp"
#include <print>
#include "Rooms.hpp"

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
        Player::Data playerData{};
        if (auto it = state.Players.find(data.PlayerId); it == state.Players.end())
        {
            playerData = it->second;
            return;
        }

        state.PlayerHistory.Save(data.PlayerId, state.CurrentReadTick, playerData);
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