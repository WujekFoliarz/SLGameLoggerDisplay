#pragma once

#include <string>
#include <vector>

#include "Locations.hpp"
#include "Events.hpp"
#include <raylib.h>
#include "AnnounceLog.hpp"
#include "ReplayState.hpp"

namespace Replay
{
    class ReplayPlayer
    {
    public:
        ReplayPlayer();
        void LoadFromFile(const std::string &filePath);
        void PollInput();
        void ProcessTicks();
        void Render();

    private:
        Replay::State m_ReplayState {};
    };
}