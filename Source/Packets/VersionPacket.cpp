#include "VersionPacket.hpp"
#include <cstring>
#include "PacketResolver.hpp"

Packet::VersionPacket::Data Packet::VersionPacket::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.Major = reader.Read<int32_t>();
    data.Minor = reader.Read<int32_t>();
    data.Build = reader.Read<int32_t>();
    return data;
}
