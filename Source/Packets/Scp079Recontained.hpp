#pragma once

#include <vector>
#include <cstdint>

namespace Packet::Scp079Recontained
{
    struct Data
    {
        int32_t PlayerId = 0;
        bool HasPlayerId = false;
    };

    Data GetResult(const std::vector<uint8_t> &inputData);
}
