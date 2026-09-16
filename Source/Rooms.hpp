#pragma once

#include <string>
#include <variant>
#include <raylib.h>

namespace Rooms
{
    enum class LczRoom
    {
        None,
        LczClassDSpawn,
        LczCrossing,
        LczCurve,
        LczAirlock,
        LczTCross,
        LczToilets,
        LczWide,
        LczLong,
        Lcz330,
        LczCheckpoint,
        LczLargeEnd,
        LczArmory,
        LczStraight,
        Count
    };

    enum class HczRoom
    {
        None,
        HczStraightPipeRoom,
        HczCurve,
        HczElevator,
        HczTesla,
        HczCrossing,
        HczIncineratorWayside,
        HczServerRoom,
        Hcz127,
        HczEndSmall,
        HczDss08,
        HczIntersection,
        HczNuke,
        HczTestRoom,
        HczIntersectionJunk,
        Hcz939,
        HczHid,
        HczEndLarge,
        HczArmory,
        HczEzCheckpoint,
        Count
    };

    enum class EzRoom
    {
        None,
        EzCollapsedTunnel,
        EzCrossing,
        EzCheckpointHallway,
        EzVent,
        EzTCross,
        EzUpstairsPcs,
        EzGateA,
        EzGateB,
        EzCurve,
        EzIntercom,
        EzStraightColumn,
        EzCafeteria,
        Count,
    };

    enum class SurfaceRoom
    {
        None,
        Surface,
        Count
    };

    void Initialize();
    std::string RoomToString(LczRoom lczRoom);
    std::string RoomToString(HczRoom hczRoom);
    std::string RoomToString(EzRoom ezRoom);
    std::string RoomToString(SurfaceRoom surfaceRoom);
    std::variant<Rooms::LczRoom, Rooms::HczRoom, Rooms::EzRoom, Rooms::SurfaceRoom> RoomNameToEnum(const std::string &roomName);
    Texture2D *GetRoomTexture(Rooms::LczRoom room);
    Texture2D *GetRoomTexture(Rooms::HczRoom room);
    Texture2D *GetRoomTexture(Rooms::EzRoom room);
    Texture2D *GetRoomTexture(Rooms::SurfaceRoom room);
}