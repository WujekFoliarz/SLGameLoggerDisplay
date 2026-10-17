#include "PlayerHurt.hpp"
#include "PacketReader.hpp"

Packet::PlayerHurt::Data Packet::PlayerHurt::GetResult(const std::vector<uint8_t> &inputData)
{
    Reader reader(inputData);
    Data data{};
    data.AttackerId = reader.Read<int32_t>();
    data.VictimId = reader.Read<int32_t>();
    data.DamageInfo = reader.ReadDotNetString();
    return data;
}
