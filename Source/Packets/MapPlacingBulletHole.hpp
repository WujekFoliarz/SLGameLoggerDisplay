#pragma once

#include <vector>
#include <cstdint>

namespace Packet::MapPlacingBulletHole
{
    struct Data
    {
        int32_t PlayerId = 0;
        bool HasPlayerId = false;
        float PositionX = 0.0f;
        float PositionY = 0.0f;
        float PositionZ = 0.0f;
        bool HasPosition = false;
    };

    Data GetResult(const std::vector<uint8_t> &inputData);
}
