#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerJoined
    {
        #pragma pack(1)
        struct Data
        {
            int32_t PlayerId = -1;
            std::string Nickname = "";
            uint8_t Role = 0;
        };
        #pragma pop(pack)

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}