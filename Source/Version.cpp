#include "Version.hpp"
#include <print>

Version::Version Version::GetVersion()
{
    return Version(1, 0, 0);
}

bool Version::IsVersionCorrect(Packet::VersionPacket::Data &data)
{
    Version versionFromData(static_cast<int>(data.Major), static_cast<int>(data.Minor), static_cast<int>(data.Build));
    Version currentVersion = GetVersion();
    if (currentVersion.Major == versionFromData.Major &&
        currentVersion.Minor == versionFromData.Minor &&
        currentVersion.Build == versionFromData.Build)
    {
        return true;
    }

    std::println("{},{},{}", versionFromData.Major,versionFromData.Minor,versionFromData.Build);

    return false;
}
