#include "DoorClosed.hpp"
#include <cstring>
#include "PacketResolver.hpp"

Packet::DoorClosed::Data Packet::DoorClosed::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.PlayerId = reader.Read<int32_t>();
    data.PositionX = reader.Read<float>();
    data.PositionY = reader.Read<float>();
    data.PositionZ = reader.Read<float>();
    return data;
}
