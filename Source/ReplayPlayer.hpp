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
        enum class FileLoadResult
        {
            Unknown,
            Success,
            VersionNotMatching,
            MissingMagic,
            FileFailedToOpen,
        };

        ReplayPlayer();
        ~ReplayPlayer();
        FileLoadResult LoadFromFile(const std::string &filePath);
        FileLoadResult LoadFromMemory(const std::vector<uint8_t>& data);
        void PollInput();
        void ProcessTicks();
        void Render();
        bool Exited();
        void Reset();

    private:
        Replay::State m_ReplayState {};
    };
}