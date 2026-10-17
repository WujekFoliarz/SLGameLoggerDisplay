#include "SCP268Used.hpp"
#include "PacketReader.hpp"

Packet::SCP268Used::Data Packet::SCP268Used::GetResult(const std::vector<uint8_t> &inputData)
{
    Reader reader(inputData);
    Data data{};
    data.PlayerId = reader.Read<int32_t>();
    return data;
}
