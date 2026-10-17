#pragma once

#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerPosition
    {
        struct Data
        {
            int32_t PlayerId = 0;
            float PositionX = 0.0f;
            float PositionY = 0.0f;
            float PositionZ = 0.0f;
            bool IsIdentity = false;
            float RotationX = 0.0f;
            float RotationY = 0.0f;
            float RotationZ = 0.0f;
            float RotationW = 0.0f;
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}