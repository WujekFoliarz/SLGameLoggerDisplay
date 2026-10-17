#include "PlayerLeft.hpp"
#include <cstring>
#include "PacketReader.hpp"

Packet::PlayerLeft::Data Packet::PlayerLeft::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);

    data.PlayerId = reader.Read<int32_t>();

    return data;
}
