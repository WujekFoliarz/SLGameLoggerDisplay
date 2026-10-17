#pragma once

#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerDied
    {
        struct Data
        {
            int32_t VictimId = 0;
            int32_t AttackerId = 0;
            uint8_t DamageType = 0;
        };

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}