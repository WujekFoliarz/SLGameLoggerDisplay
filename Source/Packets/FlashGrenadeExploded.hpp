#pragma once

#include <cstdint>
#include <vector>

namespace Packet
{
    namespace FlashGrenadeExploded
    {
        struct Data
        {
            int32_t PlayerId = 0;
            float PositionX = 0.0f;
            float PositionY = 0.0f;
            float PositionZ = 0.0f;
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}
