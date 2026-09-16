#include "PlayerDied.hpp"
#include <cstring>
#include "PacketResolver.hpp"

Packet::PlayerDied::Data Packet::PlayerDied::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.VictimId = reader.Read<int32_t>();
    data.AttackerId = reader.Read<int32_t>();
    data.DamageType = reader.Read<uint8_t>();
    return data;
}
