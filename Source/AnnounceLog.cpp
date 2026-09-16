#include "AnnounceLog.hpp"
#include <algorithm>
#include <print>
#include <sstream>
#include <string>
#include <cmath>

Vector2 AnnounceLog::AnnounceLog::Draw(int posX, int posY, float scale, bool hideText)
{
    Vector2 overallSize = Vector2(0.0f, 0.0f);
    const std::string text = GetFullText();

    const float spacing = 5.0f;
    const int startX = posX;

    Color color = WHITE;
    std::string currentTextSegment;

    auto flushText = [&]()
    {
        if (currentTextSegment.empty())
            return;

        if (!hideText)
        {
            DrawTextEx(
                GetFontDefault(),
                currentTextSegment.c_str(),
                {static_cast<float>(posX), static_cast<float>(posY)},
                scale,
                spacing,
                color);
        }

        Vector2 textSize = MeasureTextEx(
            GetFontDefault(),
            currentTextSegment.c_str(),
            scale,
            spacing);

        posX += static_cast<int>(std::round(textSize.x));

        overallSize.x = std::max(static_cast<int>(overallSize.x), posX);
        overallSize.y = std::max(static_cast<int>(overallSize.y), posY);
        int count = std::count(currentTextSegment.begin(), currentTextSegment.end(), '\n');

        currentTextSegment.clear();
    };

    const float lineHeight = scale;

    for (size_t i = 0; i < text.size();)
    {
        if (text[i] == '\n')
        {
            flushText();

            posX = startX;
            posY += static_cast<int>(std::round(lineHeight));
            color = WHITE;

            ++i;
            continue;
        }

        if (text[i] == '$')
        {
            flushText();

            const size_t end = text.find(' ', i);

            if (end == std::string::npos)
                break;

            std::string colorString = text.substr(i + 1, end - i - 1);

            std::stringstream numbers(colorString);
            std::string number;

            Color newColor = color;
            int colorNum = 0;

            while (std::getline(numbers, number, ','))
            {
                try
                {
                    const int value = std::stoi(number);

                    switch (colorNum)
                    {
                    case 0:
                        newColor.r = value;
                        break;
                    case 1:
                        newColor.g = value;
                        break;
                    case 2:
                        newColor.b = value;
                        break;
                    case 3:
                        newColor.a = value;
                        break;
                    }

                    ++colorNum;
                }
                catch (...)
                {
                    colorNum = -1;
                    break;
                }
            }

            if (colorNum == 4)
                color = newColor;

            i = end;

            continue;
        }

        currentTextSegment += text[i];
        ++i;
    }

    flushText();
    overallSize.y += std::round(scale);
    return overallSize;
}

void AnnounceLog::AnnounceLog::ShowText(const std::string &text)
{
    AnnounceLogEntry entry{};
    entry.Index = m_CurrentIndex;
    entry.Text = text;
    m_CurrentIndex++;
    m_Queue.push_back(entry);
}

void AnnounceLog::AnnounceLog::AdvanceText(float timeStep)
{
    m_CurrentTime += timeStep;

    int advanceBy = (int)(m_CurrentTime / m_AdvanceSpeed);

    if (advanceBy <= 0)
    {
        return;
    }

    std::vector<int> indexesToErase;
    bool charAdvanced = false;
    for (auto &entry : m_Queue)
    {
        if (!charAdvanced && entry.CurrentCharPos < entry.Text.size())
        {
            if (entry.Text[entry.CurrentCharPos] == '$')
            {
                entry.CurrentCharPos += 16;
            }

            entry.CurrentCharPos = std::min((int)(entry.CurrentCharPos + advanceBy), (int)entry.Text.size());
            charAdvanced = true;
        }

        if (entry.CurrentCharPos >= entry.Text.size())
        {
            entry.TimeAlive += timeStep;
        }

        if (entry.TimeAlive > entry.TimeToLive)
        {
            indexesToErase.push_back(entry.Index);
        }
    }

    for (auto &index : indexesToErase)
    {
        std::erase_if(m_Queue, [index](const AnnounceLogEntry &x)
                      { return x.Index == index; });
    }

    m_CurrentTime = 0.0f;
}

std::string AnnounceLog::AnnounceLog::GetFullText()
{
    std::string result = "";

    for (auto &entry : m_Queue)
    {
        result += entry.Text.substr(0, entry.CurrentCharPos) + "\n";
    }

    return result;
}

void AnnounceLog::AnnounceLog::Clear()
{
    m_Queue.clear();
    m_CurrentIndex = 0;
    m_CurrentTime = 0.0f;
}
