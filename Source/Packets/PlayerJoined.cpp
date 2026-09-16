#include "PlayerJoined.hpp"
#include <cstring>
#include "PacketResolver.hpp"

Packet::PlayerJoined::Data Packet::PlayerJoined::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);

    data.PlayerId = reader.Read<int32_t>();
    data.Nickname = reader.ReadDotNetString();
    data.Role = reader.Read<uint8_t>();

    return data;
}
