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
        float TickRate = 64.0f;
        size_t VisiblePoints = 0;
        Vector2 Origin{0.0f, 0.0f};
        float TotalScale = 1.0f;
        float Zoom = 1.0f;
        AnnounceLog::AnnounceLog Log;
        bool Paused = false;
        int HighlightedPlayer = -1;

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
}