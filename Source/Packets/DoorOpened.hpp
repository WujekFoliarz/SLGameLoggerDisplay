#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace DoorOpened
    {
        #pragma pack(1)
        struct Data
        {
            int32_t PlayerId = 0;
            float PositionX = 0.0f;
            float PositionY = 0.0f;
            float PositionZ = 0.0f;
        };
        #pragma pop(pack)

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}