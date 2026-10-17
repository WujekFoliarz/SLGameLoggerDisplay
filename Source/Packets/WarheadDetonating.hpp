#pragma once

#include <vector>
#include <cstdint>

namespace Packet::WarheadDetonating
{
    struct Data
    {
        int32_t PlayerId = 0;
        bool HasPlayerId = false;
    };

    Data GetResult(const std::vector<uint8_t> &inputData);
}
