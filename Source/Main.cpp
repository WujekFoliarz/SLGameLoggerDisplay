#include "ReplayPlayer.hpp"
#include "ServerBrowser.hpp"
#include "UI/UI.hpp"
#include "Fonts.hpp"
#include <print>

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Secret Lab game log display");
    SetWindowMinSize(400, 300);
    SetTargetFPS(0);
    SetExitKey(0);

    SLUI::Initialize();
    Fonts::Initialize();
    Replay::ReplayPlayer player = {};
    Server::Browser browser = {};

    bool dataDownloaded = false;
    while (!WindowShouldClose())
    {
        while (!dataDownloaded && !WindowShouldClose())
        {
            browser.PollInput();
            browser.Process();
            browser.Render();

            if (auto result = browser.GetResult(); result.has_value())
            {
                auto fileLoadResult = player.LoadFromMemory(*result);
                std::println("LoadFromMemory result: {}", static_cast<int>(fileLoadResult));
                dataDownloaded = true;
                break;
            }
        }

        if (dataDownloaded)
        {
            player.PollInput();
            player.ProcessTicks();
            player.Render();
        }

        if (player.Exited())
        {
            dataDownloaded = false;
            browser.Reset();
            player.Reset();
        }
    }

    return 0;
}