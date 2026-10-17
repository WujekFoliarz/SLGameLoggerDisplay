#include "Scp3114Strangling.hpp"
#include "PacketReader.hpp"

Packet::Scp3114Strangling::Data Packet::Scp3114Strangling::GetResult(const std::vector<uint8_t> &inputData)
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
