#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace Invalid
    {
        #pragma pack(1)
        struct Data
        {
            std::string Name = "Unknown";
        };
        #pragma pop(pack)

        Data GetResult(const std::string& eventName);
    }
}