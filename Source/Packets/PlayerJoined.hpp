#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace PlayerJoined
    {
        struct Data
        {
            int32_t PlayerId = -1;
            std::string Nickname = "";
            uint8_t Role = 0;
        };

        Data GetResult(const std::vector<uint8_t>& inputData);
    }
}