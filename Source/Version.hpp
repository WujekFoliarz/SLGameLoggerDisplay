#pragma once

#include "Packets/VersionPacket.hpp"

namespace Version
{
    enum class Compatibility
    {
        Matching,
        OutOfDate,
        NewerThanProgram,
    };

    struct Version
    {
        int Major = 0;
        int Minor = 0;
        int Build = 0;
    };

    Version GetVersion();
    Compatibility GetCompatibility(const Packet::VersionPacket::Data &data);
}