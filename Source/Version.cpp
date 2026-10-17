#include "Version.hpp"
#include <print>

Version::Version Version::GetVersion()
{
    return Version(1, 0, 1);
}

Version::Compatibility Version::GetCompatibility(const Packet::VersionPacket::Data &data)
{
    Version versionFromData(static_cast<int>(data.Major), static_cast<int>(data.Minor), static_cast<int>(data.Build));
    Version currentVersion = GetVersion();

    if (versionFromData.Major == currentVersion.Major &&
        versionFromData.Minor == currentVersion.Minor &&
        versionFromData.Build == currentVersion.Build)
    {
        return Compatibility::Matching;
    }

    if (versionFromData.Major < currentVersion.Major ||
        (versionFromData.Major == currentVersion.Major && versionFromData.Minor < currentVersion.Minor) ||
        (versionFromData.Major == currentVersion.Major && versionFromData.Minor == currentVersion.Minor && versionFromData.Build < currentVersion.Build))
    {
        return Compatibility::OutOfDate;
    }

    return Compatibility::NewerThanProgram;
}
