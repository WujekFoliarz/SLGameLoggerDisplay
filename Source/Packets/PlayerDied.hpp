#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerDied
    {
        #pragma pack(1)
        struct Data
        {
            int32_t VictimId = 0;
            int32_t AttackerId = 0;
            uint8_t DamageType = 0;
        };
        #pragma pop(pack)

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}