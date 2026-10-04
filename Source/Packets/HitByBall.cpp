#include "HitByBall.hpp"
#include "PacketResolver.hpp"

Packet::HitByBall::Data Packet::HitByBall::GetResult(const std::vector<uint8_t> &inputData)
{
    Reader reader(inputData);
    Data data{};
    data.VictimId = reader.Read<int32_t>();
    data.AttackerId = reader.Read<int32_t>();
    return data;
}
