#include "Room.hpp"
#include <cstring>
#include "PacketResolver.hpp"
#include <print>

Packet::Room::Data Packet::Room::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data{};

    Reader reader(inputData);
    data.Name = reader.ReadDotNetString();
    
    data.PositionX = reader.Read<float>();
    data.PositionY = reader.Read<float>();
    data.PositionZ = reader.Read<float>();

    data.IsIdentity = reader.Read<bool>();
    data.RotationX = reader.Read<float>();
    data.RotationY = reader.Read<float>();
    data.RotationZ = reader.Read<float>();
    data.RotationW = reader.Read<float>();
    std::println("{} x: {} y: {} z: {}", data.Name.c_str(), data.PositionX, data.PositionY, data.PositionZ);

    return data;
}
