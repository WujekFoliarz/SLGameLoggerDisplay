#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerEscorted
    {
        #pragma pack(push, 1)
        struct Data
        {
            int32_t PlayerId = 0;
            int32_t CufferId = 0;
        };
        #pragma pack(pop)

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}