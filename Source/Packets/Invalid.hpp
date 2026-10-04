#pragma once

#include "../Events.hpp"
#include <vector>
#include <cstdint>

namespace Packet
{
    namespace Invalid
    {
        #pragma pack(push, 1)
        struct Data
        {
            std::string Name = "Unknown";
        };
        #pragma pack(pop)

        Data GetResult(const std::string& eventName);
    }
}