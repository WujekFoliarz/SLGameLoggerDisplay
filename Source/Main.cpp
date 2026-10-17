#include "ReplayPlayer.hpp"
#include "ServerBrowser.hpp"
#include "UI/UI.hpp"
#include "Fonts.hpp"
#include "CrashDump.hpp"
#include <print>

int main()
{
    std::println("[Main] Starting SLGameLoggerDisplay");
    CrashDump::Initialize();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Secret Lab game log display");
    std::println("[Main] Window initialized (1280x720)");
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
                std::println("[Main] Downloaded replay: {} bytes", result->size());
                auto fileLoadResult = player.LoadFromMemory(*result);
                std::println("[Main] Replay load result: {}", static_cast<int>(fileLoadResult));
                switch (fileLoadResult)
                {
                case Replay::ReplayPlayer::FileLoadResult::Success:
                    dataDownloaded = true;
                    break;
                case Replay::ReplayPlayer::FileLoadResult::VersionOutOfDate:
                    browser.ShowLoadError("Selected file is out of date.");
                    break;
                case Replay::ReplayPlayer::FileLoadResult::VersionNewerThanProgram:
                    browser.ShowLoadError("Selected file is newer than this program.");
                    break;
                default:
                    dataDownloaded = true;
                    break;
                }

                if (dataDownloaded)
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
            std::println("[Main] Replay player exited; returning to server browser");
            dataDownloaded = false;
            browser.Reset();
            player.Reset();
        }
    }

    std::println("[Main] Shutting down");
    return 0;
}