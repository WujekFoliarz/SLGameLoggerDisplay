#pragma once

#include <cstdint>
#include <vector>

namespace Packet
{
    namespace NtfWave
    {
        struct Data
        {
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}
