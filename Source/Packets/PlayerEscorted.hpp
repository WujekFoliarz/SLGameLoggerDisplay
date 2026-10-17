#pragma once

#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerEscorted
    {
        struct Data
        {
            int32_t PlayerId = 0;
            int32_t CufferId = 0;
        };

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}