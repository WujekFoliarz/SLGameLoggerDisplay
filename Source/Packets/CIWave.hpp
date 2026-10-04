#pragma once

#include <cstdint>
#include <vector>

namespace Packet
{
    namespace CIWave
    {
        struct Data
        {
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}
