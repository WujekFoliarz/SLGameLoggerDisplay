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