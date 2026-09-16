#include "Locations.hpp"
#include "Events.hpp"
#include <print>

struct PairHash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

struct PairEqual
{
    template <class T1, class T2>
    bool operator()(const std::pair<T1, T2> &p1, const std::pair<T1, T2> &p2) const
    {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

inline static std::unordered_map<Locations::LczLayout, Vector2> LczPixelCalibration{
    {Locations::LczLayout::Stool, Vector2{-100.0f, 1702.0f}},
    {Locations::LczLayout::Clothes, Vector2{-99.5f, 1902.5f}},
    {Locations::LczLayout::Brain, Vector2{-176.0f, 1898.5f}},
    {Locations::LczLayout::Controller, Vector2{-200.5f, 1672.0f}},
    {Locations::LczLayout::Skull, Vector2{0.0f, 0.0f}}};

inline static std::unordered_map<Locations::HczLayout, Vector2> HczPixelCalibration{
    {Locations::HczLayout::CCross, Vector2{-4.0f, -0.5f}},
    {Locations::HczLayout::Split, Vector2{294.5f, -1.0f}},
    {Locations::HczLayout::Inkblot, Vector2{199.0f, 99.0f},
}};

inline static std::unordered_map<std::pair<Locations::HczLayout, Locations::EzLayout>, Vector2, PairHash, PairEqual> HczEzConnections{
    {{Locations::HczLayout::Help, Locations::EzLayout::Fractured}, {1324.5f, 200.0f}},
    {{Locations::HczLayout::Grasp, Locations::EzLayout::L}, {1221.5f, 300.0f}},
    {{Locations::HczLayout::CCross, Locations::EzLayout::Handbag}, {1121.5f, 300.0f}},
    {{Locations::HczLayout::CCross, Locations::EzLayout::Rectangles}, {1024.5f, 212.0f}},
    {{Locations::HczLayout::Inkblot, Locations::EzLayout::Handbag}, {1123.5f, 300.0f}},
    {{Locations::HczLayout::Inkblot, Locations::EzLayout::Mogus}, {1097.5f, 75.0f}},
    {{Locations::HczLayout::Split, Locations::EzLayout::Mogus}, {992.0f, -25.0f}},
};

Locations::Zone Locations::GetZoneFromHeight(float height)
{
    if (height >= 98.0f && height <= 120.0f)
        return Zone::Lcz;

    if (height >= -180.0f && height <= -90.0f)
        return Zone::HczEz;

    if (height >= 270.0f && height <= 320.0f)
        return Zone::Outside;

    return Zone::Unknown;
}