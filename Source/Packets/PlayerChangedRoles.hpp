#pragma once

#include <vector>
#include <cstdint>

namespace Packet::PlayerChangedRoles
{
    struct Data
    {
        int32_t PlayerId = 0;
        uint8_t Role = 0;
    };

    Data GetResult(const std::vector<uint8_t> &inputData);
}
