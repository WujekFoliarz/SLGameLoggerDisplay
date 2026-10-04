#pragma once

#include "Packets/VersionPacket.hpp"

namespace Version
{
    struct Version
    {
        int Major = 0;
        int Minor = 0;
        int Build = 0;
    };

    Version GetVersion();
    bool IsVersionCorrect(Packet::VersionPacket::Data &data);
}