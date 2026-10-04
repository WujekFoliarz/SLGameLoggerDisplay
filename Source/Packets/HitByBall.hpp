#pragma once

#include <cstdint>
#include <vector>

namespace Packet
{
    namespace HitByBall
    {
        struct Data
        {
            int32_t VictimId = 0;
            int32_t AttackerId = 0;
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}
