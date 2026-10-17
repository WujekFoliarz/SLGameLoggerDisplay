#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Packet
{
    namespace PlayerHurt
    {
        struct Data
        {
            int32_t AttackerId = 0;
            int32_t VictimId = 0;
            std::string DamageInfo;
        };

        Data GetResult(const std::vector<uint8_t> &inputData);
    }
}
