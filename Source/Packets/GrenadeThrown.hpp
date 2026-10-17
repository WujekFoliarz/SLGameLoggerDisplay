#pragma once

#include <vector>
#include <cstdint>

namespace Packet
{
    namespace GrenadeThrown
    {
        struct Data
        {
            int32_t PlayerId = 0;
        };

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}