#include "PlayerEscaped.hpp"
#include <cstring>
#include "PacketReader.hpp"

Packet::PlayerEscaped::Data Packet::PlayerEscaped::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.PlayerId = reader.Read<int32_t>();
    return data;
}
