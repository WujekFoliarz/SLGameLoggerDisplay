#include "FlashGrenadeThrown.hpp"
#include "PacketResolver.hpp"

Packet::FlashGrenadeThrown::Data Packet::FlashGrenadeThrown::GetResult(const std::vector<uint8_t> &inputData)
{
    Reader reader(inputData);
    Data data{};
    data.PlayerId = reader.Read<int32_t>();
    return data;
}
