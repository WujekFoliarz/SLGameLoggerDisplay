#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerPosition
    {
#pragma pack(push, 1)
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
#pragma pack(pop)

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}