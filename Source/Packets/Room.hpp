#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace Packet
{
    namespace Room
    {
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

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}