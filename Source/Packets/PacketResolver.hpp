#pragma once

#include <variant>
#include <cstring>

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
#include "FlashGrenadeThrown.hpp"
#include "FlashGrenadeExploded.hpp"
#include "SCP268Used.hpp"
#include "SCP268Expired.hpp"

namespace Packet
{
    using Variant = std::variant<Packet::Invalid::Data, Packet::NewTick::Data, Packet::Room::Data,
                                Packet::PlayerJoined::Data, Packet::PlayerPosition::Data, Packet::PlayerChangedRoles::Data,
                                Packet::PlayerLeft::Data, Packet::DoorOpened::Data, Packet::PlayerDied::Data,
                                Packet::DoorClosed::Data, Packet::CancelChargingMicroHid::Data, Packet::ChargingMicroHid::Data,
                                Packet::FiringMicroHid::Data, Packet::PlayerEscaped::Data, Packet::PlayerEscorted::Data,
                                Packet::VersionPacket::Data, Packet::NtfWave::Data, Packet::NtfMiniWave::Data,
                                Packet::CIWave::Data, Packet::CIMiniWave::Data, Packet::BallThrown::Data,
                                Packet::HitByBall::Data, Packet::GrenadeThrown::Data, Packet::GrenadeExploded::Data,
                                Packet::PickingUpItem::Data, Packet::FlashGrenadeThrown::Data,
                                Packet::FlashGrenadeExploded::Data, Packet::SCP268Used::Data,
                                Packet::SCP268Expired::Data>;
    Variant Resolve(Events::EventEnum event, const std::vector<uint8_t> &data);

    class Reader
    {
    public:
        Reader(const std::vector<uint8_t> &data);
        std::string ReadDotNetString();
        std::vector<uint8_t> ReadBytes(int size);
        bool HasRemaining(size_t bytes) const;

        template <typename T>
        T Read()
        {
            static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

            if (!HasRemaining(sizeof(T)))
            {
                return T{};
            }

            T result = 0;
            std::memcpy(&result, m_Data->data() + m_Offset, sizeof(T));
            m_Offset += static_cast<int>(sizeof(T));
            return result;
        }

    private:
        int m_Offset = 0;
        std::vector<uint8_t> *m_Data = nullptr;
    };
}