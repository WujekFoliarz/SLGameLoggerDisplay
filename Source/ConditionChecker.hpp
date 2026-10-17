#pragma once
#include <raylib.h>
#include "PointParams.hpp"
#include "Events.hpp"

namespace ConditionChecker
{
    struct ConditionCheckResult
    {
        std::string AnnounceLogMessage = "";
        PointParams::Icon Icon = PointParams::Icon::None;
        bool DontRender = true;
        Color IconColor = WHITE;
    };

    ConditionCheckResult GetResult(const Events::Point &point);
}