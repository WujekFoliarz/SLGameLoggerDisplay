#pragma once

#include <unordered_map>
#include <nlohmann/json.hpp>
#include <raylib.h>

namespace Locations
{
    enum class Zone
    {
        Unknown,
        Lcz,
        HczEz,
        Outside
    };

    enum class LczLayout
    {
        Unk,
        Clothes,
        Stool,
        Brain,
        Controller,
        Skull
    };

    enum class HczLayout
    {
        Unk,
        CCross,
        Grasp,
        Help,
        Inkblot,
        NewCircuit,
        NewTall,
        RottenHeart,
        Split,
        Storm,
        TopSquares
    };

    enum class EzLayout
    {
        Unk,
        Rectangles,
        Mogus,
        L,
        Handbag,
        Fractured
    };

    Zone GetZoneFromHeight(float height);
}