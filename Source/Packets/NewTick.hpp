#pragma once

#include <vector>
#include <cstdint>

namespace Packet
{
    namespace NewTick
    {
        struct Data
        {
            int64_t Tick = 0;
        };

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}