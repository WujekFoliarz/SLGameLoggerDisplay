#include "PlayerChangedRoles.hpp"
#include <cstring>
#include "PacketResolver.hpp"

Packet::PlayerChangedRoles::Data Packet::PlayerChangedRoles::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.PlayerId = reader.Read<int32_t>();
    data.Role = reader.Read<uint8_t>();
    return data;
}
