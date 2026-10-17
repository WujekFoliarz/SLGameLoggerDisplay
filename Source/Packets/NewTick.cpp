#include "NewTick.hpp"
#include <cstring>
#include "PacketReader.hpp"

Packet::NewTick::Data Packet::NewTick::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.Tick = reader.Read<int64_t>();
    return data;
}
