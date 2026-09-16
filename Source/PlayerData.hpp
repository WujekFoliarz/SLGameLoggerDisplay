#pragma once

#include <raylib.h>
#include "Events.hpp"

namespace Player
{
    struct Data
    {
        std::string Nickname = "[UNSET NICKNAME]";
        Vector3 Position = {};
        Quaternion Rotation = {};
        Events::RoleTypeId Role = Events::RoleTypeId::None;
    };
}