#include "PickingUpItem.hpp"
#include "PacketResolver.hpp"

Packet::PickingUpItem::Data Packet::PickingUpItem::GetResult(const std::vector<uint8_t> &inputData)
{
    Reader reader(inputData);
    Data data{};
    data.PlayerId = reader.Read<int32_t>();
    data.ItemId = reader.ReadDotNetString();
    data.PositionX = reader.Read<float>();
    data.PositionY = reader.Read<float>();
    data.PositionZ = reader.Read<float>();
    return data;
}
