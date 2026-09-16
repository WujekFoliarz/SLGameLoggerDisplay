#include "PlayerPosition.hpp"
#include "PacketResolver.hpp"
#include <cstring>
#include <print>

Packet::PlayerPosition::Data Packet::PlayerPosition::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.PlayerId = reader.Read<int32_t>();
    data.PositionX = reader.Read<float>();
    data.PositionY = reader.Read<float>();
    data.PositionZ = reader.Read<float>();
    data.IsIdentity = reader.Read<bool>();
    data.RotationX = reader.Read<float>();
    data.RotationY = reader.Read<float>();
    data.RotationZ = reader.Read<float>();
    data.RotationW = reader.Read<float>();
    return data;
}
