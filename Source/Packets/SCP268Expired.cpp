#include "SCP268Expired.hpp"
#include "PacketResolver.hpp"

Packet::SCP268Expired::Data Packet::SCP268Expired::GetResult(const std::vector<uint8_t> &inputData)
{
    Reader reader(inputData);
    Data data{};
    data.PlayerId = reader.Read<int32_t>();
    return data;
}
