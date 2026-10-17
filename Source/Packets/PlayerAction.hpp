#pragma once

#include <cstdint>
#include <vector>
#include "../Events.hpp"

namespace Packet
{
    namespace PlayerAction
    {
        struct Data
        {
            int32_t PlayerId = 0;
            int32_t TargetId = 0;
            Events::EventEnum Event = Events::EventEnum::None;
            float PositionX = 0.0f;
            float PositionY = 0.0f;
            float PositionZ = 0.0f;
        };

        Data GetResult(Events::EventEnum event, const std::vector<uint8_t> &inputData);
    }
}
