#include "raylib.h"

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <print>
#include <algorithm>

#include <nlohmann/json.hpp>

#include "Events.hpp"
#include "Locations.hpp"
#include "AnnounceLog.hpp"
#include "ReplayPlayer.hpp"

int main()
{
    Replay::ReplayPlayer player {};
    player.LoadFromFile("log.scpd");

    while (!WindowShouldClose())
    {
        player.PollInput();
        player.ProcessTicks();
        player.Render();
    }

    return 0;
}