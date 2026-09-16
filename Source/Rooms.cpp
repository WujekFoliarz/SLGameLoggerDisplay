#include "Rooms.hpp"
#include <unordered_map>
#include <cassert>
#include <print>

inline static bool Intialized = false;
inline static std::unordered_map<Rooms::LczRoom, Texture2D> LczRoomTextureMap;
inline static std::unordered_map<Rooms::HczRoom, Texture2D> HczRoomTextureMap;
inline static std::unordered_map<Rooms::EzRoom, Texture2D> EzRoomTextureMap;
inline static std::unordered_map<Rooms::SurfaceRoom, Texture2D> SurfaceRoomTextureMap;

void Rooms::Initialize()
{
    if (Intialized)
    {
        return;
    }

    for (int i = 1; i < (int)Rooms::LczRoom::Count; i++)
    {
        Texture2D texture = LoadTexture(std::string(RESOURCE_PATH "Rooms/LCZ/" + Rooms::RoomToString((Rooms::LczRoom)i) + ".png").c_str());
        if (IsTextureValid(texture))
        {
            LczRoomTextureMap.emplace((Rooms::LczRoom)i, std::move(texture));
        }
    }

    for (int i = 1; i < (int)Rooms::HczRoom::Count; i++)
    {
        Texture2D texture = LoadTexture(std::string(RESOURCE_PATH "Rooms/HCZ/" + Rooms::RoomToString((Rooms::HczRoom)i) + ".png").c_str());
        if (IsTextureValid(texture))
        {
            HczRoomTextureMap.emplace((Rooms::HczRoom)i, std::move(texture));
        }
    }

    for (int i = 1; i < (int)Rooms::EzRoom::Count; i++)
    {
        Texture2D texture = LoadTexture(std::string(RESOURCE_PATH "Rooms/EZ/" + Rooms::RoomToString((Rooms::EzRoom)i) + ".png").c_str());
        if (IsTextureValid(texture))
        {
            EzRoomTextureMap.emplace((Rooms::EzRoom)i, std::move(texture));
        }
    }

    for (int i = 1; i < (int)Rooms::SurfaceRoom::Count; i++)
    {
        Texture2D texture = LoadTexture(std::string(RESOURCE_PATH "Rooms/Surface/" + Rooms::RoomToString((Rooms::SurfaceRoom)i) + ".png").c_str());
        if (IsTextureValid(texture))
        {
            SurfaceRoomTextureMap.emplace((Rooms::SurfaceRoom)i, std::move(texture));
        }
    }

    Intialized = true;
}

std::string Rooms::RoomToString(Rooms::LczRoom lczRoom)
{
    switch (lczRoom)
    {
    case Rooms::LczRoom::LczClassDSpawn:
        return "LczClassDSpawn";
    case Rooms::LczRoom::LczCrossing:
        return "LczCrossing";
    case Rooms::LczRoom::LczCurve:
        return "LczCurve";
    case Rooms::LczRoom::LczAirlock:
        return "LczAirlock";
    case Rooms::LczRoom::LczTCross:
        return "LczTCross";
    case Rooms::LczRoom::LczToilets:
        return "LczToilets";
    case Rooms::LczRoom::LczWide:
        return "LczWide";
    case Rooms::LczRoom::LczLong:
        return "LczLong";
    case Rooms::LczRoom::Lcz330:
        return "Lcz330";
    case Rooms::LczRoom::LczCheckpoint:
        return "LczCheckpoint";
    case Rooms::LczRoom::LczLargeEnd:
        return "LczLargeEnd";
    case Rooms::LczRoom::LczArmory:
        return "LczArmory";
    case Rooms::LczRoom::LczStraight:
        return "LczStraight";
    }

    return "Unknown";
}

std::string Rooms::RoomToString(Rooms::HczRoom hczRoom)
{
    switch (hczRoom)
    {
    case Rooms::HczRoom::HczStraightPipeRoom:
        return "HczStraightPipeRoom";
    case Rooms::HczRoom::HczCurve:
        return "HczCurve";
    case Rooms::HczRoom::HczElevator:
        return "HczElevator";
    case Rooms::HczRoom::HczTesla:
        return "HczTesla";
    case Rooms::HczRoom::HczCrossing:
        return "HczCrossing";
    case Rooms::HczRoom::HczIncineratorWayside:
        return "HczIncineratorWayside";
    case Rooms::HczRoom::HczServerRoom:
        return "HczServerRoom";
    case Rooms::HczRoom::Hcz127:
        return "Hcz127";
    case Rooms::HczRoom::HczEndSmall:
        return "HczEndSmall";
    case Rooms::HczRoom::HczDss08:
        return "HczDss08";
    case Rooms::HczRoom::HczIntersection:
        return "HczIntersection";
    case Rooms::HczRoom::HczNuke:
        return "HczNuke";
    case Rooms::HczRoom::HczTestRoom:
        return "HczTestRoom";
    case Rooms::HczRoom::HczIntersectionJunk:
        return "HczIntersectionJunk";
    case Rooms::HczRoom::Hcz939:
        return "Hcz939";
    case Rooms::HczRoom::HczHid:
        return "HczHid";
    case Rooms::HczRoom::HczEndLarge:
        return "HczEndLarge";
    case Rooms::HczRoom::HczArmory:
        return "HczArmory";
    case Rooms::HczRoom::HczEzCheckpoint:
        return "HczEzCheckpoint";
    }

    return "Unknown";
}

std::string Rooms::RoomToString(EzRoom ezRoom)
{
    switch (ezRoom)
    {
    case Rooms::EzRoom::EzCollapsedTunnel:
        return "EzCollapsedTunnel";
    case Rooms::EzRoom::EzCrossing:
        return "EzCrossing";
    case Rooms::EzRoom::EzCheckpointHallway:
        return "EzCheckpointHallway";
    case Rooms::EzRoom::EzVent:
        return "EzVent";
    case Rooms::EzRoom::EzTCross:
        return "EzTCross";
    case Rooms::EzRoom::EzUpstairsPcs:
        return "EzUpstairsPcs";
    case Rooms::EzRoom::EzGateA:
        return "EzGateA";
    case Rooms::EzRoom::EzGateB:
        return "EzGateB";
    case Rooms::EzRoom::EzCurve:
        return "EzCurve";
    case Rooms::EzRoom::EzIntercom:
        return "EzIntercom";
    case Rooms::EzRoom::EzStraightColumn:
        return "EzStraightColumn";
    case Rooms::EzRoom::EzCafeteria:
        return "EzCafeteria";
    }

    return "Unknown";
}

std::string Rooms::RoomToString(Rooms::SurfaceRoom surfaceRoom)
{
    switch (surfaceRoom)
    {
    case Rooms::SurfaceRoom::Surface:
        return "Surface";
    }

    return "Unknown";
}

std::variant<Rooms::LczRoom, Rooms::HczRoom, Rooms::EzRoom, Rooms::SurfaceRoom> Rooms::RoomNameToEnum(const std::string &roomName)
{
    if (roomName == "LczClassDSpawn")
        return Rooms::LczRoom::LczClassDSpawn;
    if (roomName == "LczCrossing")
        return Rooms::LczRoom::LczCrossing;
    if (roomName == "LczCurve")
        return Rooms::LczRoom::LczCurve;
    if (roomName == "LczAirlock")
        return Rooms::LczRoom::LczAirlock;
    if (roomName == "LczTCross")
        return Rooms::LczRoom::LczTCross;
    if (roomName == "LczToilets")
        return Rooms::LczRoom::LczToilets;
    if (roomName == "LczWide")
        return Rooms::LczRoom::LczWide;
    if (roomName == "LczLong")
        return Rooms::LczRoom::LczLong;
    if (roomName == "Lcz330")
        return Rooms::LczRoom::Lcz330;
    if (roomName == "LczCheckpointA")
        return Rooms::LczRoom::LczCheckpoint;
    if (roomName == "LczCheckpointB")
        return Rooms::LczRoom::LczCheckpoint;
    if (roomName == "Lcz173")
        return Rooms::LczRoom::LczLargeEnd;
    if (roomName == "Lcz914")
        return Rooms::LczRoom::LczLargeEnd;
    if (roomName == "LczGlassBox")
        return Rooms::LczRoom::LczLargeEnd;
    if (roomName == "LczArmory")
        return Rooms::LczRoom::LczArmory;
    if (roomName == "LczPlants")
        return Rooms::LczRoom::LczWide;
    if (roomName == "LczStraight")
        return Rooms::LczRoom::LczStraight;
    if (roomName == "LczCafe")
        return Rooms::LczRoom::LczLargeEnd;

    if (roomName == "HczStraightPipeRoom")
        return Rooms::HczRoom::HczStraightPipeRoom;
    if (roomName == "HczCurve")
        return Rooms::HczRoom::HczCurve;
    if (roomName == "HczCornerDeep")
        return Rooms::HczRoom::HczCurve;
    if (roomName == "HczElevatorA")
        return Rooms::HczRoom::HczElevator;
    if (roomName == "HczElevatorB")
        return Rooms::HczRoom::HczElevator;
    if (roomName == "HczTesla")
        return Rooms::HczRoom::HczTesla;
    if (roomName == "HczCrossing")
        return Rooms::HczRoom::HczCrossing;
    if (roomName == "HczLoadingBay")
        return Rooms::HczRoom::HczIntersection;
    if (roomName == "HczIncineratorWayside")
        return Rooms::HczRoom::HczIncineratorWayside;
    if (roomName == "HczServerRoom")
        return Rooms::HczRoom::HczServerRoom;
    if (roomName == "Hcz127")
        return Rooms::HczRoom::Hcz127;
    if (roomName == "Hcz096")
        return Rooms::HczRoom::HczEndSmall;
    if (roomName == "HczDss08")
        return Rooms::HczRoom::HczDss08;
    if (roomName == "HczIntersection")
        return Rooms::HczRoom::HczIntersection;
    if (roomName == "HczNuke")
        return Rooms::HczRoom::HczNuke;
    if (roomName == "HczTestRoom")
        return Rooms::HczRoom::HczTestRoom;
    if (roomName == "HczIntersectionJunk")
        return Rooms::HczRoom::HczIntersectionJunk;
    if (roomName == "Hcz939")
        return Rooms::HczRoom::Hcz939;
    if (roomName == "HczHid")
        return Rooms::HczRoom::HczHid;
    if (roomName == "Hcz106")
        return Rooms::HczRoom::HczEndLarge;
    if (roomName == "Hcz079")
        return Rooms::HczRoom::HczEndLarge;
    if (roomName == "HczArmory")
        return Rooms::HczRoom::HczArmory;
    if (roomName == "HczEzCheckpointA")
        return Rooms::HczRoom::HczEzCheckpoint;
    if (roomName == "HczEzCheckpointB")
        return Rooms::HczRoom::HczEzCheckpoint;
    if (roomName == "HczStraightC")
        return Rooms::HczRoom::HczEzCheckpoint;
    if (roomName == "HczStraight")
        return Rooms::HczRoom::HczEzCheckpoint;

    if (roomName == "EzCollapsedTunnel")
        return Rooms::EzRoom::EzCollapsedTunnel;
    if (roomName == "EzCrossing")
        return Rooms::EzRoom::EzCrossing;
    if (roomName == "EzCheckpointHallwayA")
        return Rooms::EzRoom::EzCheckpointHallway;
    if (roomName == "EzCheckpointHallwayB")
        return Rooms::EzRoom::EzCheckpointHallway;
    if (roomName == "EzShelter")
        return Rooms::EzRoom::EzVent;
    if (roomName == "EzTCross")
        return Rooms::EzRoom::EzTCross;
    if (roomName == "EzPcs")
        return Rooms::EzRoom::EzUpstairsPcs;
    if (roomName == "EzDownstairsPcs")
        return Rooms::EzRoom::EzUpstairsPcs;
    if (roomName == "EzUpstairsPcs")
        return Rooms::EzRoom::EzCafeteria;
    if (roomName == "EzGateA")
        return Rooms::EzRoom::EzGateA;
    if (roomName == "EzGateB")
        return Rooms::EzRoom::EzGateB;
    if (roomName == "EzCurve")
        return Rooms::EzRoom::EzCurve;
    if (roomName == "EzIntercom")
        return Rooms::EzRoom::EzIntercom;
    if (roomName == "EzStraightColumn")
        return Rooms::EzRoom::EzStraightColumn;
    if (roomName == "EzChef")
        return Rooms::EzRoom::EzStraightColumn;
    if (roomName == "EzCafeteria")
        return Rooms::EzRoom::EzStraightColumn;
    if (roomName == "EzConference")
        return Rooms::EzRoom::EzStraightColumn;
    if (roomName == "EzSmallrooms")
        return Rooms::EzRoom::EzStraightColumn;
    if (roomName == "EzVent")
        return Rooms::EzRoom::EzVent;

    if (roomName == "Surface")
        return Rooms::SurfaceRoom::Surface;

    //std::println("{}", roomName);
    return Rooms::LczRoom::None;
}

Texture2D *Rooms::GetRoomTexture(Rooms::LczRoom room)
{
    assert(Intialized);

    if (auto it = LczRoomTextureMap.find(room); it != LczRoomTextureMap.end())
    {
        return &it->second;
    }

    return nullptr;
}

Texture2D *Rooms::GetRoomTexture(Rooms::HczRoom room)
{
    assert(Intialized);

    if (auto it = HczRoomTextureMap.find(room); it != HczRoomTextureMap.end())
    {
        return &it->second;
    }

    return nullptr;
}

Texture2D *Rooms::GetRoomTexture(Rooms::EzRoom room)
{
    assert(Intialized);

    if (auto it = EzRoomTextureMap.find(room); it != EzRoomTextureMap.end())
    {
        return &it->second;
    }

    return nullptr;
}

Texture2D *Rooms::GetRoomTexture(Rooms::SurfaceRoom room)
{
    assert(Intialized);

    if (auto it = SurfaceRoomTextureMap.find(room); it != SurfaceRoomTextureMap.end())
    {
        return &it->second;
    }

    return nullptr;
}
