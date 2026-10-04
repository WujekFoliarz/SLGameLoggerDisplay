#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerLeft
    {
        #pragma pack(push, 1)
        struct Data
        {
            int32_t PlayerId = -1;
        };
        #pragma pack(pop)

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}