#pragma once

#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerLeft
    {
        struct Data
        {
            int32_t PlayerId = -1;
        };

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}