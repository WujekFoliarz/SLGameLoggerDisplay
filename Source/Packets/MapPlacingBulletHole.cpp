#include "MapPlacingBulletHole.hpp"
#include "PacketReader.hpp"

Packet::MapPlacingBulletHole::Data Packet::MapPlacingBulletHole::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data{};
    Reader reader(inputData);
    if (reader.HasRemaining(sizeof(data.PlayerId)))
    {
        data.PlayerId = reader.Read<int32_t>();
        data.HasPlayerId = true;
    }
    if (reader.HasRemaining(sizeof(data.PositionX) + sizeof(data.PositionY) + sizeof(data.PositionZ)))
    {
        data.PositionX = reader.Read<float>();
        data.PositionY = reader.Read<float>();
        data.PositionZ = reader.Read<float>();
        data.HasPosition = true;
    }
    return data;
}
