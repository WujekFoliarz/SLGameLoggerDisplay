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

namespace Packet
{
    using Variant = std::variant<Packet::Invalid::Data, Packet::NewTick::Data, Packet::Room::Data,
                                Packet::PlayerJoined::Data, Packet::PlayerPosition::Data, Packet::PlayerChangedRoles::Data,
                                Packet::PlayerLeft::Data, Packet::DoorOpened::Data, Packet::PlayerDied::Data,
                                Packet::DoorClosed::Data, Packet::CancelChargingMicroHid::Data, Packet::ChargingMicroHid::Data,
                                Packet::FiringMicroHid::Data, Packet::PlayerEscaped::Data, Packet::PlayerEscorted::Data>;
    Variant Resolve(Events::EventEnum event, const std::vector<uint8_t> &data);

    class Reader
    {
    public:
        Reader(const std::vector<uint8_t> &data);
        std::string ReadDotNetString();

        template <typename T>
        T Read()
        {
            T result = 0;
            std::memcpy(&result, m_Data->data() + m_Offset, sizeof(T));
            m_Offset += sizeof(T);
            return result;
        }

    private:
        int m_Offset = 0;
        std::vector<uint8_t> *m_Data = nullptr;
    };
}