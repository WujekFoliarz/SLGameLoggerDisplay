#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace Packet
{
    namespace Invalid
    {
        struct Data
        {
            std::string Name = "Unknown";
        };

        Data GetResult(const std::string& eventName);
    }
}