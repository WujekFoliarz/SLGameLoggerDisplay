#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace VersionPacket
    {
        #pragma pack(push, 1)
        struct Data
        {
            int32_t Major = 0;
            int32_t Minor = 0;
            int32_t Build = 0;
        };
        #pragma pack(pop)

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}