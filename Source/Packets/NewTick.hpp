#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace NewTick
    {
        #pragma pack(push, 1)
        struct Data
        {
            int64_t Tick = 0;
        };
        #pragma pack(pop)

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}