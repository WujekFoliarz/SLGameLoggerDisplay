#include "Utils.hpp"
#include <iomanip>

std::string Utils::GetRoundTimeString(float currentTick, int tickRate)
{
    int totalSeconds = (currentTick / tickRate);
    int seconds = totalSeconds % 60;
    int minutes = totalSeconds / 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds;

    return oss.str();
}