#if defined(_WIN32)
#define _WIN32_WINNT 0x0A00
#define WINVER 0x0A00
#include "external/fix_win32_compatibility.h"
#endif

#include "ServerBrowser.hpp"
#include <print>
#include <httplib.h>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include "UI/Scale.hpp"
#include "Fonts.hpp"

Server::Browser::Browser()
{
    m_CircleTexture = LoadTexture(RESOURCE_PATH "General/LoadCircle.png");
    m_Servers.clear();
    m_Loading = false;
    RefreshServerHeaders();
}

Server::Browser::~Browser()
{
    UnloadTexture(m_CircleTexture);
}

void Server::Browser::PollInput()
{
    if (!m_Selected)
        m_HighlightedServer = -1;
    int currentServerIndex = 0;
    for (auto &header : m_Servers)
    {
        if (!m_Selected && header.Rect.width > 0.0f && header.Rect.height > 0.0f &&
            CheckCollisionPointRec(GetMousePosition(), header.Rect))
        {
            m_HighlightedServer = currentServerIndex;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                m_Selected = true;
                m_SelectedServerAddress = header.Address;
                RefreshFileHeader(header.Address);
            }
        }

        currentServerIndex++;
    }

    int currentFileIndex = 0;
    for (auto &header : m_Files)
    {
        if (m_Selected && !m_FileSelected && CheckCollisionPointRec(GetMousePosition(), header.Rect))
        {
            m_HighlightedFile = currentFileIndex;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                m_FileSelected = true;
                m_Result.clear();
                m_Downloading = true;
#ifdef __EMSCRIPTEN__
                m_Result = DownloadData(m_SelectedServerAddress, header.FileName);
                m_Downloading = false;
#else
                m_DownloadFuture = std::async(std::launch::async, [this, httpAddress = m_SelectedServerAddress, fileName = header.FileName]()
                                              { return DownloadData(httpAddress, fileName); });
#endif
            }
        }

        currentFileIndex++;
    }

    if (m_Selected && CheckCollisionPointRec(GetMousePosition(), m_BackButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        m_Selected = false;
        m_SelectedServerAddress.clear();
        m_FileSelected = false;
        m_HighlightedFile = -1;
        m_Files.clear();
        m_Result.clear();
        m_ServerListScroll = 0;
        m_FileListScroll = 0.0f;
        return;
    }
}

void Server::Browser::Process()
{
    if (m_Loading && m_ServerRefreshFuture.valid() && m_ServerRefreshFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
    {
        m_Servers = m_ServerRefreshFuture.get();
        m_ServerListScroll = 0;
        m_ServerListDragging = false;
        m_HighlightedServer = -1;
        m_Loading = false;
    }

    if (m_FileListLoading && m_FileRefreshFuture.valid() && m_FileRefreshFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
    {
        m_Files = m_FileRefreshFuture.get();
        m_FileListLoading = false;
    }

    if (m_Downloading && m_DownloadFuture.valid() && m_DownloadFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
    {
        m_Result = m_DownloadFuture.get();
        m_Downloading = false;
    }
}

void Server::Browser::Render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (m_Downloading)
    {
        RenderLoadingWheel(GetScreenWidth() / 2, GetScreenHeight() / 2, 200);
        EndDrawing();
        return;
    }

    float screenHeight = GetScreenHeight();
    float screenWidth = GetScreenWidth();

    static constexpr int kBaseHeaderTextScale = 100;
    int headerTextScale = kBaseHeaderTextScale * SLUI::GetScale();
    auto headerTextSize = MeasureTextEx(Fonts::GetFont(Fonts::FontType::TwoWeekendGoSemibold), "SCP: SL Replay Player", headerTextScale, 5);
    float headerTextPosY = 50;
    DrawTextEx(Fonts::GetFont(Fonts::FontType::TwoWeekendGoSemibold), "SCP: SL Replay Player", {(screenWidth / 2) - (headerTextSize.x / 2), headerTextPosY}, headerTextScale, 5, WHITE);

    int panelPosY = headerTextPosY + 10;
    Rectangle panelRectangle = {};
    panelRectangle.height = screenHeight - 200;
    panelRectangle.width = screenWidth - 100;
    panelRectangle.x = (screenWidth / 2) - (panelRectangle.width / 2);
    panelRectangle.y = headerTextPosY + headerTextSize.y + 5;
    DrawRectangleLinesEx(panelRectangle, 5, WHITE);

    if (m_Loading)
    {
        RenderLoadingWheel(panelRectangle.x + (panelRectangle.width / 2), panelRectangle.y + (panelRectangle.height / 2), 200);
        EndDrawing();
        return;
    }

    if (m_Servers.empty())
    {
        static constexpr int kBaseServerTextScale = 48;
        int serverTextScale = kBaseServerTextScale * SLUI::GetScale();
        const std::string emptyText = "No servers available";
        const auto emptySize = MeasureTextEx(GetFontDefault(), emptyText.c_str(), serverTextScale, 5);
        const float centerX = panelRectangle.x + (panelRectangle.width / 2.0f);
        const float centerY = panelRectangle.y + (panelRectangle.height / 2.0f);

        DrawText(emptyText.c_str(), centerX - (emptySize.x / 2.0f), centerY - 20.0f, serverTextScale, WHITE);
        EndDrawing();
        return;
    }

    static constexpr int kBaseServerTextScale = 50;
    int serverTextScale = kBaseServerTextScale * SLUI::GetScale();
    constexpr float padding = 5.0f;
    const float linePosX = static_cast<int>(panelRectangle.x + 30.0f);
    const float listTop = panelRectangle.y + 10.0f;
    const float listBottom = panelRectangle.y + panelRectangle.height - 10.0f;
    const float listHeight = listBottom - listTop;
    const float rowHeight = MeasureTextEx(GetFontDefault(), "Ag", serverTextScale, 5).y + padding;
    const int visibleRows = std::max(1, static_cast<int>(listHeight / rowHeight));
    const int maxScroll = std::max(0, static_cast<int>(m_Servers.size()) - visibleRows);

    Rectangle listViewport{
        panelRectangle.x + 20.0f,
        listTop,
        panelRectangle.width - 40.0f,
        listHeight};
    if (CheckCollisionPointRec(GetMousePosition(), listViewport))
    {
        const int wheelMove = static_cast<int>(std::round(GetMouseWheelMove()));
        m_ServerListScroll = std::clamp(m_ServerListScroll - wheelMove, 0, maxScroll);
    }

    m_ServerListScroll = std::clamp(m_ServerListScroll, 0, maxScroll);

    const float scrollbarTrackWidth = 12.0f;
    Rectangle scrollbarTrack{
        panelRectangle.x + panelRectangle.width - 28.0f,
        listTop,
        scrollbarTrackWidth,
        listHeight};
    const float thumbHeight = maxScroll > 0
                                  ? std::min(listHeight, std::max(32.0f, listHeight * visibleRows / static_cast<float>(m_Servers.size())))
                                  : listHeight;
    const float thumbTravel = std::max(0.0f, listHeight - thumbHeight);
    auto getThumbRect = [&]()
    {
        const float thumbY = listTop + (maxScroll > 0
                                            ? thumbTravel * m_ServerListScroll / static_cast<float>(maxScroll)
                                            : 0.0f);
        return Rectangle{scrollbarTrack.x, thumbY, scrollbarTrack.width, thumbHeight};
    };

    if (maxScroll > 0)
    {
        const Vector2 mousePosition = GetMousePosition();
        Rectangle thumbRect = getThumbRect();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            (CheckCollisionPointRec(mousePosition, scrollbarTrack) ||
             CheckCollisionPointRec(mousePosition, thumbRect)))
        {
            if (!CheckCollisionPointRec(mousePosition, thumbRect))
            {
                const float scrollRatio = std::clamp(
                    (mousePosition.y - listTop - thumbHeight / 2.0f) / std::max(1.0f, thumbTravel),
                    0.0f,
                    1.0f);
                m_ServerListScroll = static_cast<int>(std::round(scrollRatio * maxScroll));
            }

            m_ServerListDragging = true;
            m_ServerListDragStartY = mousePosition.y;
            m_ServerListDragStartScroll = m_ServerListScroll;
        }

        if (m_ServerListDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            const float deltaY = mousePosition.y - m_ServerListDragStartY;
            const float scrollRatio = deltaY / std::max(1.0f, thumbTravel);
            m_ServerListScroll = std::clamp(
                m_ServerListDragStartScroll + static_cast<int>(std::round(scrollRatio * maxScroll)),
                0,
                maxScroll);
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            m_ServerListDragging = false;
        }
    }
    else
    {
        m_ServerListDragging = false;
    }

    for (auto &header : m_Servers)
        header.Rect = {};

    BeginScissorMode(
        static_cast<int>(listViewport.x),
        static_cast<int>(listViewport.y),
        static_cast<int>(listViewport.width),
        static_cast<int>(listViewport.height));

    for (int visibleIndex = 0; visibleIndex < visibleRows; ++visibleIndex)
    {
        const int serverIndex = m_ServerListScroll + visibleIndex;
        if (serverIndex >= static_cast<int>(m_Servers.size()))
            break;

        auto &header = m_Servers[serverIndex];
        const float rowY = listTop + visibleIndex * rowHeight;
        header.Rect = {
            static_cast<float>(linePosX),
            rowY,
            panelRectangle.width - 60.0f,
            rowHeight};

        if (m_HighlightedServer == serverIndex)
            DrawRectangleRec(header.Rect, Color(128, 128, 128, 100));

        DrawLine(linePosX, static_cast<int>(rowY), linePosX + static_cast<int>(header.Rect.width), static_cast<int>(rowY), WHITE);
        DrawTextEx(Fonts::GetFont(Fonts::FontType::TwoWeekendGoRegular), header.Motd.c_str(), {linePosX, rowY + padding / 2.0f}, serverTextScale, 5, WHITE);
        DrawLine(linePosX, static_cast<int>(rowY + rowHeight), linePosX + static_cast<int>(header.Rect.width), static_cast<int>(rowY + rowHeight), WHITE);
    }

    EndScissorMode();

    if (maxScroll > 0)
    {
        DrawRectangleRounded(scrollbarTrack, 0.8f, 4, Color(50, 50, 50, 180));
        DrawRectangleRounded(getThumbRect(), 0.8f, 4, Color(180, 180, 180, 220));
    }

    if (m_Selected)
    {
        RenderReplayFileList();
    }

    EndDrawing();
}

std::optional<std::vector<uint8_t>> Server::Browser::GetResult()
{
    if (m_Result.empty())
    {
        return std::nullopt;
    }

    std::vector<uint8_t> result = std::move(m_Result);
    m_Result.clear();
    return result;
}

void Server::Browser::Reset()
{
    m_Selected = false;
    m_SelectedServerAddress.clear();
    m_FileSelected = false;
    m_HighlightedServer = -1;
    m_HighlightedFile = -1;
    m_ServerListScroll = 0;
    m_ServerListDragging = false;
    m_Downloading = false;
    m_Loading = false;
    m_FileListLoading = false;
    m_Result.clear();
    m_Files.clear();
}

std::vector<std::string> Server::Browser::GetServerList()
{
    std::vector<std::string> list;

    const auto appendServers = [&list](std::istream &serverList)
    {
        std::string line;
        while (std::getline(serverList, line))
        {
            std::stringstream lineStream(line);
            std::string candidate;
            while (lineStream >> candidate)
            {
                if (candidate.rfind('#', 0) == 0)
                {
                    break;
                }

                if (!candidate.empty() && candidate.find("http://") == 0)
                {
                    if (std::find(list.begin(), list.end(), candidate) == list.end())
                    {
                        list.push_back(candidate);
                    }
                }
            }
        }
    };

    std::ifstream serverListFile("ServerList.txt");
    if (serverListFile.is_open())
    {
        appendServers(serverListFile);
    }

    try
    {
        httplib::Client client("http://raw.githubusercontent.com");
        client.set_connection_timeout(3, 0);
        client.set_read_timeout(3, 0);
        client.set_follow_location(true);

        const auto response = client.Get("/WujekFoliarz/SLGameLoggerDisplay/main/ServerList.txt");
        if (response && response->status == 200)
        {
            std::istringstream remoteServerList(response->body);
            appendServers(remoteServerList);
        }
        else if (response)
        {
            std::println("Remote server list request failed: HTTP {}", response->status);
        }
        else
        {
            std::println("Remote server list request failed: {}", httplib::to_string(response.error()));
        }
    }
    catch (const std::exception &e)
    {
        std::println("Remote server list request failed: {}", e.what());
    }

    return list;
}

void Server::Browser::RefreshServerHeaders()
{
    m_Loading = true;
    m_Servers.clear();
#ifdef __EMSCRIPTEN__
    m_Loading = false;
    return;
#else
    m_ServerRefreshFuture = std::async(std::launch::async, [this]()
                                       {
        std::vector<ServerHeader> refreshedServers;
        for (auto &httpAddress : GetServerList())
        {
            httplib::Client cli(httpAddress);
            if (auto res = cli.Get("/motd"))
            {
                if (res->status == 200)
                {
                    ServerHeader header = {};
                    header.Motd = res->body;
                    header.Address = httpAddress;
                    refreshedServers.push_back(header);
                }
            }
        }

        return refreshedServers; });
#endif
}

void Server::Browser::RefreshFileHeader(const std::string &httpAddress)
{
    m_FileListLoading = true;
    m_FileListScroll = 0.0f;
#ifdef __EMSCRIPTEN__
    m_Files.clear();
    m_FileListLoading = false;
    return;
#else
    m_FileRefreshFuture = std::async(std::launch::async, [this, httpAddress]()
                                     {
        std::vector<FileHeader> refreshedFiles;
        httplib::Client cli(httpAddress);
        if (auto res = cli.Get("/files"))
        {
            if (res->status == 200)
            {
                nlohmann::json json = nlohmann::json::parse(res->body);

                for (auto &entry : json)
                {
                    const std::string fileName = entry["name"].get<std::string>();
                    const size_t fileSize = entry["sizeBytes"].get<size_t>();

                    FileHeader header = {};
                    header.FileName = fileName;
                    header.FileSize = fileSize;
                    refreshedFiles.push_back(header);
                }
            }
        }

        return refreshedFiles; });
#endif
}

std::vector<uint8_t> Server::Browser::DownloadData(const std::string &httpAddress, const std::string &fileName)
{
#ifdef __EMSCRIPTEN__
    return {};
#else
    try
    {
        httplib::Client cli(httpAddress);

        const auto path = "/files/" + fileName;

        auto res = cli.Get(path);

        if (!res)
        {
            std::println(
                "Download failed: {} {}", httpAddress, httplib::to_string(res.error()));
            return {};
        }

        std::println("HTTP status: {}", res->status);

        if (res->status == 200)
        {
            std::println("File Downloaded");
            return {
                res->body.begin(),
                res->body.end()};
        }

        std::println("HTTP error: {}", res->status);
    }
    catch (const std::exception &e)
    {
        std::println("Exception: {}", e.what());
    }

    return {};
#endif
}

void Server::Browser::RenderReplayFileList()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawRectangle(0, 0, screenWidth, screenHeight, Color(0, 0, 0, 200));

    if (m_FileListLoading || m_Downloading)
    {
        RenderLoadingWheel(GetScreenWidth() / 2, GetScreenHeight() / 2, 200);
        return;
    }

    float posX = screenWidth * 0.1f;
    float posBackBtnX = screenWidth * 0.01f;
    const int padding = 10;
    auto backTextSize = MeasureTextEx(GetFontDefault(), "Back", 60 * SLUI::GetScale(), 10);
    m_BackButton.width = backTextSize.x;
    m_BackButton.height = backTextSize.y;
    m_BackButton.x = posBackBtnX;
    DrawRectangleRounded(m_BackButton, 0.2f, 6, Color(80, 80, 80, 220));
    DrawText("Back", posBackBtnX + padding, m_BackButton.y, 60 * SLUI::GetScale(), WHITE);

    static constexpr int kBaseFileNameTextScale = 50;
    float listTop = m_BackButton.y + m_BackButton.height + padding;
    const float listHeight = screenHeight * 0.75f;
    float endPosX = screenWidth - (screenWidth * 0.1f);
    int headerTextScale = kBaseFileNameTextScale * SLUI::GetScale();

    float contentHeight = 0.0f;
    for (const auto &header : m_Files)
    {
        Vector2 textSize = MeasureTextEx(GetFontDefault(), header.FileName.c_str(), headerTextScale, 5);
        contentHeight += textSize.y + (padding * 2.0f);
    }

    float maxScroll = std::max(0.0f, contentHeight - listHeight);
    float wheelMove = GetMouseWheelMove();
    if (wheelMove != 0.0f)
    {
        m_FileListScroll -= wheelMove * 30.0f;
        m_FileListScroll = std::clamp(m_FileListScroll, 0.0f, maxScroll);
    }

    const float scrollbarTrackX = endPosX + 12.0f;
    const float scrollbarTrackY = listTop;
    const float scrollbarTrackWidth = 12.0f;
    const float scrollbarTrackHeight = listHeight;
    const float thumbHeight = std::max(32.0f, (listHeight / std::max(1.0f, contentHeight)) * listHeight);
    float thumbY = scrollbarTrackY + (m_FileListScroll / std::max(1.0f, maxScroll)) * std::max(1.0f, scrollbarTrackHeight - thumbHeight);

    Rectangle trackRect = {scrollbarTrackX, scrollbarTrackY, scrollbarTrackWidth, scrollbarTrackHeight};
    Rectangle thumbRect = {scrollbarTrackX, thumbY, scrollbarTrackWidth, thumbHeight};

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(GetMousePosition(), trackRect))
        {
            m_FileListDragging = true;
            m_FileListDragStartY = GetMouseY();
            m_FileListDragStartScroll = m_FileListScroll;
        }
    }

    if (m_FileListDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        const float deltaY = GetMouseY() - m_FileListDragStartY;
        const float dragableHeight = std::max(1.0f, scrollbarTrackHeight - thumbHeight);
        const float targetScroll = m_FileListDragStartScroll + (deltaY / dragableHeight) * maxScroll;
        m_FileListScroll = std::clamp(targetScroll, 0.0f, maxScroll);
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        m_FileListDragging = false;
    }

    DrawRectangleRounded(trackRect, 0.8f, 4, Color(50, 50, 50, 180));
    DrawRectangleRounded(thumbRect, 0.8f, 4, Color(180, 180, 180, 220));

    float currentY = listTop - m_FileListScroll;
    for (int i = 0; i < m_Files.size(); i++)
    {
        auto &header = m_Files[i];
        Vector2 textSize = MeasureTextEx(GetFontDefault(), header.FileName.c_str(), headerTextScale, 5);
        float itemHeight = textSize.y + (padding * 2.0f);

        if (currentY + itemHeight < listTop)
        {
            currentY += itemHeight;
            continue;
        }

        if (currentY > listTop + listHeight)
        {
            break;
        }

        header.Rect.x = posX;
        header.Rect.y = currentY;
        header.Rect.width = endPosX - posX;
        header.Rect.height = itemHeight;

        DrawLine(posX, currentY, endPosX, currentY, WHITE);
        DrawTextEx(Fonts::GetFont(Fonts::FontType::TwoWeekendGoRegular), header.FileName.c_str(), {posX + padding, currentY + padding}, headerTextScale, 5, WHITE);

        DrawLine(posX, currentY + itemHeight, endPosX, currentY + itemHeight, WHITE);
        currentY += itemHeight;
    }

    if (m_HighlightedFile >= 0 && m_HighlightedFile < static_cast<int>(m_Files.size()))
    {
        auto &header = m_Files[m_HighlightedFile];
        DrawRectangleRec(header.Rect, Color(128, 128, 128, 100));
    }
}

void Server::Browser::RenderLoadingWheel(float posX, float posY, float size)
{
    float circleScale = size * SLUI::GetScale();
    Rectangle rect = {};
    rect.height = m_CircleTexture.height;
    rect.width = m_CircleTexture.width;
    rect.x = 0;
    rect.y = 0;

    Rectangle destRect = {};
    destRect.height = circleScale;
    destRect.width = circleScale;
    destRect.x = posX;
    destRect.y = posY;

    DrawTexturePro(m_CircleTexture, rect, destRect, Vector2(destRect.width / 2, destRect.height / 2), GetTime() * 700.0f, WHITE);
}
