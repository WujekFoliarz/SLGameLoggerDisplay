#pragma once

#include <cstdint>
#include <vector>

namespace Packet
{
    namespace NtfMiniWave
    {
        struct Data
        {
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}
