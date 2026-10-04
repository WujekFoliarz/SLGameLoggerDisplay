#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <future>
#include <raylib.h>
#include <atomic>
#include <optional>

namespace Server
{
    static inline constexpr int kMaxServerCount = 32;
    static inline constexpr int kMaxFileCount = 128;

    struct ServerHeader
    {
        std::string Motd = "";
        std::string Address = "";
        Rectangle Rect = {};
    };

    struct FileHeader
    {
        std::string FileName = "";
        size_t FileSize = 0;
        Rectangle Rect = {};
    };

    class Browser
    {
    public:
        Browser();
        ~Browser();
        void PollInput();
        void Process();
        void Render();
        std::optional<std::vector<uint8_t>> GetResult();
        void Reset();

    private:
        std::vector<std::string> GetServerList();
        void RefreshServerHeaders();
        void RefreshFileHeader(const std::string &httpAddress);
        std::vector<uint8_t> DownloadData(const std::string &httpAddress, const std::string &fileName);
        void RenderReplayFileList();
        void RenderLoadingWheel(float posX, float posY, float size);

        Texture2D m_CircleTexture = {};
        std::vector<ServerHeader> m_Servers;
        std::vector<FileHeader> m_Files;
        std::future<std::vector<ServerHeader>> m_ServerRefreshFuture;
        std::future<std::vector<FileHeader>> m_FileRefreshFuture;
        std::future<std::vector<uint8_t>> m_DownloadFuture;
        int m_HighlightedServer = -1;
        int m_HighlightedFile = -1;
        int m_ServerListScroll = 0;
        bool m_ServerListDragging = false;
        float m_ServerListDragStartY = 0.0f;
        int m_ServerListDragStartScroll = 0;
        float m_FileListScroll = 0.0f;
        float m_FileListDragStartY = 0.0f;
        float m_FileListDragStartScroll = 0.0f;
        bool m_FileListDragging = false;
        std::atomic<bool> m_Loading = false;
        std::atomic<bool> m_FileListLoading = false;
        bool m_Selected = false;
        std::string m_SelectedServerAddress;
        bool m_FileSelected = false;
        std::atomic<bool> m_Downloading = false;
        std::vector<uint8_t> m_Result;
        Rectangle m_BackButton = {30.0f,30.0f,220.0f,48.0f};};
}