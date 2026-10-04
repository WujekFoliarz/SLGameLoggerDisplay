#include "BallThrown.hpp"
#include "PacketResolver.hpp"

Packet::BallThrown::Data Packet::BallThrown::GetResult(const std::vector<uint8_t> &inputData)
{
    Reader reader(inputData);
    Data data{};
    data.PlayerId = reader.Read<int32_t>();
    return data;
}
