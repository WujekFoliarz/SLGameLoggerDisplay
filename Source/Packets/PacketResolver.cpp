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
