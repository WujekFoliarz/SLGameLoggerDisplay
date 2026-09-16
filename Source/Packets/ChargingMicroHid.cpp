#include "ChargingMicroHid.hpp"
#include <cstring>
#include "PacketResolver.hpp"

Packet::ChargingMicroHid::Data Packet::ChargingMicroHid::GetResult(const std::vector<uint8_t> &inputData)
{
    Data data = {};
    Reader reader(inputData);
    data.PlayerId = reader.Read<int32_t>();
    return data;
}
