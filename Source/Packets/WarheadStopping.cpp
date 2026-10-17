#include "WarheadStopping.hpp"
#include "PacketReader.hpp"

Packet::WarheadStopping::Data Packet::WarheadStopping::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data{};
    Reader reader(inputData);
    if (reader.HasRemaining(sizeof(data.PlayerId)))
    {
        data.PlayerId = reader.Read<int32_t>();
        data.HasPlayerId = true;
    }
    return data;
}
