#include "PlayerEscorted.hpp"
#include <cstring>
#include "PacketResolver.hpp"

Packet::PlayerEscorted::Data Packet::PlayerEscorted::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.PlayerId = reader.Read<int32_t>();
    data.CufferId = reader.Read<int32_t>();
    return data;
}
