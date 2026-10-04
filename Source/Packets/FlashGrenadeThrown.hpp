#pragma once

#include <cstdint>
#include <vector>

namespace Packet
{
    namespace FlashGrenadeThrown
    {
        struct Data
        {
            int32_t PlayerId = 0;
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}
