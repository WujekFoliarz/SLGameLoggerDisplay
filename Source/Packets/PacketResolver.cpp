#include "PacketResolver.hpp"
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
    default:
        return Invalid::GetResult(Events::EventToString(event));
    }

    return Invalid::GetResult("Unknown");
}

Packet::Reader::Reader(const std::vector<uint8_t> &data)
{
    m_Data = const_cast<std::vector<uint8_t> *>(&data);
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