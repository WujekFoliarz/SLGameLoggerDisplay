#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace Room
    {
        #pragma pack(1)
        struct Data
        {
            std::string Name = "";

            float PositionX = 0.0f;
            float PositionY = 0.0f;
            float PositionZ = 0.0f;

            bool IsIdentity = false;
            float RotationX = 0.0f;
            float RotationY = 0.0f;
            float RotationZ = 0.0f;
            float RotationW = 0.0f;
        };
        #pragma pop(pack)

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}