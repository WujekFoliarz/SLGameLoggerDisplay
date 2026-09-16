#pragma once

#include <string>
#include <vector>
#include <raylib.h>

namespace AnnounceLog
{

    struct AnnounceLogEntry
    {
        int Index = 0;
        std::string Text = "";
        int CurrentCharPos = 0;
        float TimeAlive = 0.0f;
        float TimeToLive = 1.0f;
    };

    class AnnounceLog
    {
    public:
        Vector2 Draw(int posX, int posY, float scale, bool hideText = false);
        void ShowText(const std::string &text);
        void AdvanceText(float timeStep);
        std::string GetFullText();
        void Clear();
    private:
        std::vector<AnnounceLogEntry> m_Queue;
        float m_AdvanceSpeed = 0.007f;
        float m_CurrentTime = 0.0f;
        int m_CurrentIndex = 0;
    };
}