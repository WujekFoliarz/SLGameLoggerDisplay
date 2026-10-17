#include "PlayerAction.hpp"
#include "PacketReader.hpp"

Packet::PlayerAction::Data Packet::PlayerAction::GetResult(
    Events::EventEnum event,
    const std::vector<uint8_t> &inputData)
{
    Reader reader(inputData);
    Data data{};
    data.PlayerId = reader.Read<int32_t>();
    data.TargetId = reader.Read<int32_t>();
    data.Event = event;
    data.PositionX = reader.Read<float>();
    data.PositionY = reader.Read<float>();
    data.PositionZ = reader.Read<float>();
    return data;
}
