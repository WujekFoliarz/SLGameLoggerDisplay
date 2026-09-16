#include "ReplayPlayer.hpp"
#include <cstdio>
#include <print>
#include <algorithm>
#include <cmath>

#include "rlImGui.h"
#include "PointParams.hpp"
#include "Rooms.hpp"
#include "AnnounceLog.hpp"
#include "Utils.hpp"
#include "ConditionChecker.hpp"
#include "UI/Toolbox/Window.hpp"
#include "UI/ControlPanel/Window.hpp"
#include "UI/AnnounceLog/Window.hpp"
#include "UI/UI.hpp"
#include "UI/Scale.hpp"
#include "Packets/PacketResolver.hpp"

float outsideScale = 1.2260439f;
Vector2 outsideOffset = {256.0f, 56.5f};

Replay::ReplayPlayer::ReplayPlayer()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Secret Lab game log display");
    SetWindowMinSize(400, 300);
    SetTargetFPS(180);
    SetExitKey(0);

    PointParams::Initialize();
    Rooms::Initialize();
    UI::Initialize();
}

void Replay::ReplayPlayer::LoadFromFile(const std::string &filePath)
{
    m_ReplayState.Points.clear();

    FILE *file = std::fopen(filePath.c_str(), "rb");
    if (file == nullptr)
    {
        std::println("File {} could not be opened", filePath);
        return;
    }

    int currentTick = 0;
    while (true)
    {
        uint8_t packetType = 0;
        uint16_t packetLength = 0;

        if (std::fread(&packetType, 1, sizeof(packetType), file) != sizeof(packetType))
            break;

        if (std::fread(&packetLength, 1, sizeof(packetLength), file) != sizeof(packetLength))
            break;

        std::vector<uint8_t> data(packetLength);

        if (std::fread(data.data(), 1, data.size(), file) != data.size())
            break;

        auto event = static_cast<Events::EventEnum>(packetType);
        auto packet = Packet::Resolve(event, data);

        if (event == Events::EventEnum::NewTick)
        {
            currentTick = std::get<Packet::NewTick::Data>(packet).Tick;
            m_ReplayState.TickCount = currentTick;
        }
        if (event == Events::EventEnum::Room)
        {
            HandlePacket(std::get<Packet::Room::Data>(packet), m_ReplayState, false);
            continue;
        }

        m_ReplayState.Data[currentTick].push_back(packet);
    }

    std::fclose(file);
    std::println("[Replay::ReplayPlayer::LoadFromFile] Loaded {}/{} ticks", m_ReplayState.Data.size(), m_ReplayState.TickCount);
}

void Replay::ReplayPlayer::PollInput()
{
    static bool dragging = false;
    static Vector2 dragAnchor = {0.0f, 0.0f};
    static Vector2 panAnchor = {0.0f, 0.0f};
    static Vector2 pan = {0.0f, 0.0f};

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    float fitScale = 10.0f;

    // Mouse wheel zoom, centered on the cursor
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
    {
        Vector2 mouseBefore = GetMousePosition();
        float totalScaleBefore = fitScale * m_ReplayState.Zoom;
        Vector2 worldUnderMouse =
            {
                (mouseBefore.x - pan.x) / totalScaleBefore,
                (mouseBefore.y - pan.y) / totalScaleBefore};

        m_ReplayState.Zoom *= (wheel > 0) ? 1.1f : (1.0f / 1.1f);
        m_ReplayState.Zoom = std::clamp(m_ReplayState.Zoom, 0.1f, 10.0f);

        float totalScaleAfter = fitScale * m_ReplayState.Zoom;
        pan.x = mouseBefore.x - worldUnderMouse.x * totalScaleAfter;
        pan.y = mouseBefore.y - worldUnderMouse.y * totalScaleAfter;
    }

    // Right-drag to pan
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        dragging = true;
        dragAnchor = GetMousePosition();
        panAnchor = pan;
    }
    if (dragging)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mouse = GetMousePosition();
            pan.x = panAnchor.x + (mouse.x - dragAnchor.x);
            pan.y = panAnchor.y + (mouse.y - dragAnchor.y);
        }
        else
        {
            dragging = false;
        }
    }

    if (IsKeyDown(KEY_BACKSPACE))
    {
        m_ReplayState.CurrentTick = 0;
        m_ReplayState.VisiblePoints = 0;

        for (auto &p : m_ReplayState.Points)
        {
            p.Opacity = 1.0f;
            p.Handled = false;
        }
    }

    if (IsKeyPressed(KEY_L))
    {
        m_ReplayState.Log.ShowText("This$255,255,0,255 is a test!");
    }

    m_ReplayState.TotalScale = fitScale * m_ReplayState.Zoom;
    m_ReplayState.Origin = pan;
}

void Replay::ReplayPlayer::ProcessTicks()
{
    if (!m_ReplayState.Paused && m_ReplayState.CurrentTick < m_ReplayState.TickCount)
    {
        m_ReplayState.CurrentTick += GetFrameTime() * m_ReplayState.TickRate * m_ReplayState.PlaySpeed;
        if (m_ReplayState.CurrentTick < 0)
            m_ReplayState.CurrentTick = 0;
    }

    int startTick = (int)m_ReplayState.PreviousTick;
    int endTick = (int)m_ReplayState.CurrentTick;

    for (int tick = startTick; tick < endTick; tick++)
    {
        m_ReplayState.CurrentReadTick = tick;
        if (auto it = m_ReplayState.Data.find(tick); it != m_ReplayState.Data.end())
        {
            for (auto &packet : it->second)
            {
                std::visit([this](const auto &packet)
                           { Replay::HandlePacket(packet, m_ReplayState, false); }, packet);
            }
        }
    }

    for (int tick = startTick; tick > endTick; tick--)
    {
        m_ReplayState.CurrentReadTick = tick;
        if (auto it = m_ReplayState.Data.find(tick); it != m_ReplayState.Data.end())
        {
            for (auto &packet : it->second)
            {
                std::visit([this](const auto &packet)
                           { Replay::HandlePacket(packet, m_ReplayState, true); }, packet);
            }
        }
    }

    if (!m_ReplayState.Paused && m_ReplayState.CurrentTick < m_ReplayState.TickCount)
        m_ReplayState.PreviousTick = m_ReplayState.CurrentTick;
    // else if (m_ReplayState.Paused && m_ReplayState.CurrentTick != m_ReplayState.PreviousTick)
    // m_ReplayState.PreviousTick = m_ReplayState.CurrentTick - 2;
    m_ReplayState.Log.AdvanceText(GetFrameTime());
}

void Replay::ReplayPlayer::Render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    while (m_ReplayState.VisiblePoints < m_ReplayState.Points.size() && m_ReplayState.Points[m_ReplayState.VisiblePoints].Tick <= m_ReplayState.CurrentTick)
    {
        m_ReplayState.VisiblePoints++;
    }

    static auto QuaternionToYAngleDegrees = [](float w, float x, float y, float z)
    {
        float angleRad = 2.0f * std::atan2(y, w);
        return angleRad * (180.0f / (float)PI);
    };

    // Render rooms
    {
        for (auto &roomData : m_ReplayState.RoomPositions)
        {
            auto roomEnum = Rooms::RoomNameToEnum(roomData.Name);
            Texture2D *roomTexture = std::visit([](auto &&room)
                                                { return Rooms::GetRoomTexture(room); }, roomEnum);
            bool isOutside = false;
            if (std::holds_alternative<Rooms::SurfaceRoom>(roomEnum))
            {
                isOutside = true;
            }

            float texPixelX = roomData.Position.x;
            float texPixelY = roomData.Position.z;

            if (isOutside)
            {
                texPixelX += 200;
                texPixelY += 80;
            }
            if (Locations::GetZoneFromHeight(roomData.Position.y) == Locations::Zone::HczEz)
            {
                texPixelY += 110;
            }

            float screenX = m_ReplayState.Origin.x + texPixelX * m_ReplayState.TotalScale;
            float screenY = m_ReplayState.Origin.y + texPixelY * m_ReplayState.TotalScale;
            float screenXOutside = m_ReplayState.Origin.x + outsideOffset.x * m_ReplayState.TotalScale;
            float screenYOutside = m_ReplayState.Origin.y + outsideOffset.y * m_ReplayState.TotalScale;

            if (roomTexture && IsTextureValid(*roomTexture))
            {
                float scale = isOutside ? outsideScale * m_ReplayState.Zoom : m_ReplayState.Zoom * 0.58f;

                float textureWidth = roomTexture->width * scale;
                float textureHeight = roomTexture->height * scale;

                float rotationDeg = QuaternionToYAngleDegrees(roomData.Rotation.w, -roomData.Rotation.x, -roomData.Rotation.y, -roomData.Rotation.z);

                Rectangle source = {0.0f, 0.0f, (float)roomTexture->width, -(float)roomTexture->height};
                Rectangle dest = {isOutside ? screenXOutside : screenX, isOutside ? screenYOutside : screenY, textureWidth, textureHeight};
                Vector2 origin = {textureWidth * 0.5f, textureHeight * 0.5f};

                DrawTexturePro(*roomTexture, source, dest, origin, rotationDeg, Color(255, 255, 255, 200));
            }
            else
                DrawText(roomData.Name.c_str(), screenX, screenY, 2 * m_ReplayState.TotalScale, YELLOW);
        }
    }

    // Render points
    {
        std::vector<int> pointsForRemoval;
        for (size_t i = 0; i < m_ReplayState.VisiblePoints; i++)
        {
            auto zone = Locations::GetZoneFromHeight(m_ReplayState.Points[i].Position.y);
            auto &p = m_ReplayState.Points[i];
            p.Id = i;

            if (p.Opacity <= 0.0f)
            {
                pointsForRemoval.push_back(i);
                continue;
            }

            float dx = p.Position.x;
            float dz = p.Position.z;

            float texPixelX = dx;
            float texPixelY = dz;

            if (zone == Locations::Zone::HczEz)
            {
                texPixelY += 110;
            }
            else if (zone == Locations::Zone::Outside)
            {
                texPixelX += 200;
                texPixelY += 80;
            }

            float screenX = m_ReplayState.Origin.x + texPixelX * m_ReplayState.TotalScale;
            float screenY = m_ReplayState.Origin.y + texPixelY * m_ReplayState.TotalScale;
            // std::println("outside x: {} | outside y: {} | outside scale: {}", outsideOffset.x, outsideOffset.y, outsideScale);

            float radius = std::clamp(5.5f * m_ReplayState.Zoom, 1.5f, 50.0f);

            auto fadeOut = (unsigned char)std::max(0, std::min(255, (int)std::floor(p.Opacity * 256.0)));
            auto eventResult = ConditionChecker::GetResult(p);
            p.Handled = true;

            auto iconTexture = PointParams::GetIconTexture(eventResult.Icon);
            if (eventResult.UseDotInsteadOfIcon || iconTexture == nullptr)
            {
                DrawCircle(static_cast<int>(screenX), static_cast<int>(screenY), radius, Color{eventResult.IconColor.r, eventResult.IconColor.g, eventResult.IconColor.b, fadeOut});
            }
            else
            {

                float textureWidth = iconTexture->width * 0.5f;
                float textureHeight = iconTexture->height * 0.5f;

                Rectangle source = {0.0f, 0.0f, (float)iconTexture->width, (float)iconTexture->height};
                Rectangle dest = {screenX, screenY, textureWidth, textureHeight};
                Vector2 origin = {textureWidth * 0.5f, textureHeight * 0.5f};

                DrawTexturePro(*iconTexture, source, dest, origin, 0, {eventResult.IconColor.r, eventResult.IconColor.g, eventResult.IconColor.b, fadeOut});
                //DrawTextureEx(*iconTexture, Vector2(screenX, screenY), 0.0f, 0.5f, {eventResult.IconColor.r, eventResult.IconColor.g, eventResult.IconColor.b, fadeOut});
            }

            if (!eventResult.AnnounceLogMessage.empty())
            {
                m_ReplayState.Log.ShowText(Utils::GetRoundTimeString(p.Tick, m_ReplayState.TickRate) + " " + eventResult.AnnounceLogMessage);
            }

            p.Opacity -= PointParams::GetDecayRate(p.Event) * GetFrameTime();
        }

        for (auto index : pointsForRemoval)
        {
            std::erase_if(m_ReplayState.Points, [index](const Events::Point &x)
                          { return x.Id == index; });
        }
        pointsForRemoval.clear();
    }

    // Render player rectangles
    {
        for (auto &[id, data] : m_ReplayState.Players)
        {
            if (data.Role == Events::RoleTypeId::Spectator || data.Role == Events::RoleTypeId::Scp079 || data.Role == Events::RoleTypeId::Destroyed)
                continue;

            auto iconTexture = PointParams::GetIconTexture(PointParams::Icon::PlayerPosition);
            if (iconTexture == nullptr || !IsTextureValid(*iconTexture))
            {
                continue;
            }

            float dx = data.Position.x;
            float dz = data.Position.z;

            float texPixelX = dx;
            float texPixelY = dz;

            auto zone = Locations::GetZoneFromHeight(data.Position.y);

            if (zone == Locations::Zone::HczEz)
            {
                texPixelY += 110;
            }
            else if (zone == Locations::Zone::Outside)
            {
                texPixelX += 200;
                texPixelY += 80;
            }

            float screenX = m_ReplayState.Origin.x + texPixelX * m_ReplayState.TotalScale;
            float screenY = m_ReplayState.Origin.y + texPixelY * m_ReplayState.TotalScale;

            float rotationDeg = QuaternionToYAngleDegrees(data.Rotation.w, -data.Rotation.x, -data.Rotation.y, -data.Rotation.z);

            float textureWidth = iconTexture->width * 0.3f;
            float textureHeight = iconTexture->height * 0.3f;

            Rectangle source = {0.0f, 0.0f, (float)iconTexture->width, -(float)iconTexture->height};
            Rectangle dest = {screenX, screenY, textureWidth, textureHeight};
            Vector2 origin = {textureWidth * 0.5f, textureHeight * 0.5f};

            DrawTexturePro(*iconTexture, source, dest, origin, rotationDeg, PointParams::GetRoleColor(data.Role));

            if (id == m_ReplayState.HighlightedPlayer)
            {
                Rectangle destLarger = {screenX, screenY, textureWidth * 2.0f, textureHeight * 2.0f};
                Vector2 originLarger = {destLarger.width * 0.5f, destLarger.height * 0.5f};
                float alpha = 152.5f + 102.5f * sinf(GetTime() * 10.0f);
                DrawPolyLinesEx(Vector2(screenX, screenY), 3, 30.0f, rotationDeg + 90.0f, 5.0f, Color(255, 255, 0, alpha));
            }
        }
    }

    // Draw UI
    {
        rlImGuiBegin();
        UI::ApplyScale();
        UI::Toolbox::Render(m_ReplayState);
        UI::ControlPanel::Render(m_ReplayState);
        UI::AnnounceLog::Render(m_ReplayState);
        rlImGuiEnd();
    }

    EndDrawing();
}
