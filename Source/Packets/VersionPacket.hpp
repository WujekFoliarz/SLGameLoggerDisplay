#pragma once

#include <vector>
#include <cstdint>

namespace Packet
{
    namespace VersionPacket
    {
        struct Data
        {
            int32_t Major = 0;
            int32_t Minor = 0;
            int32_t Build = 0;
        };

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}