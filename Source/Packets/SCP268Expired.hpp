#pragma once

#include <cstdint>
#include <vector>

namespace Packet
{
    namespace SCP268Expired
    {
        struct Data
        {
            int32_t PlayerId = 0;
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}
