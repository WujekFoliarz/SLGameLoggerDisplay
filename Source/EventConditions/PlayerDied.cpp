#include "PlayerDied.hpp"
#include <string>
#include <format>
#include <print>
#include <functional>

#include "../DamageType.hpp"
#include "../PointParams.hpp"

std::unordered_map<Damage::Type, const char *> LogMessage1PlayerMap = {
    {Damage::Type::Unknown, "Player [{}] {} died"},
    {Damage::Type::Tesla, "Player [{}] {} died on Tesla Gate"},
    {Damage::Type::Explosion, "Player [{}] {} died in an Explosion"},
    {Damage::Type::PocketDimension, "Player [{}] {} died in Pocket Dimension"},
    {Damage::Type::Recontainment, "Player [{}] {} died in Recontamination"},
    {Damage::Type::Scp939, "Player [{}] {} died to $255,0,0,255SCP-939"}, /// ???
};

std::unordered_map<Damage::Type, const char *> LogMessage2PlayerMap = {
    {Damage::Type::Scp173, "Player [{}] {} got their neck snapped by [{}] {}"},
    {Damage::Type::Scp939, "Player [{}] {} was slashed by [{}] {}"},
    {Damage::Type::Scp106, "Player [{}] {} was corroded by [{}] {}"},
    {Damage::Type::Fsp9, "Player [{}] {} was shot with Fsp-9 by [{}] {}"},
    {Damage::Type::Com18, "Player [{}] {} was shot with Com-18 by [{}] {}"},
    {Damage::Type::AK, "Player [{}] {} was shot with AK by [{}] {}"},
    {Damage::Type::Logicer, "Player [{}] {} was shot with Logicer by [{}] {}"},
    {Damage::Type::MicroHid, "Player [{}] {} was electrocuted with MicroHID by [{}] {}"},
    {Damage::Type::Crossvec, "Player [{}] {} was shot with Crossvec by [{}] {}"},
    {Damage::Type::Shotgun, "Player [{}] {} was shot with Shotgun by [{}] {}"},
    {Damage::Type::Scp0492, "Player [{}] {} was killed by [{}] {}"},
    {Damage::Type::Explosion, "Player [{}] {} died in an Explosion caused by [{}] {}"},
    {Damage::Type::Frmg0, "Player [{}] {} was shot with FR-MG-0 by [{}] {}"},
    {Damage::Type::E11Sr, "Player [{}] {} was shot with MTF-E11-SR by [{}] {}"}};

std::vector<std::function<PointParams::Icon(const Damage::Type)>> IconFunctions =
    {
        [](const Damage::Type data)
        {
            if (data == Damage::Type::Fsp9 ||
                data == Damage::Type::Com18 ||
                data == Damage::Type::AK ||
                data == Damage::Type::Crossvec ||
                data == Damage::Type::Shotgun ||
                data == Damage::Type::Frmg0 ||
                data == Damage::Type::E11Sr ||
                data == Damage::Type::Logicer)
            {
                return PointParams::Icon::PlayerShot;
            }

            return PointParams::Icon::PlayerEliminated;
        },
        [](const Damage::Type data)
        {
            if (data == Damage::Type::Scp173)
            {
                return PointParams::Icon::NeckSnapped;
            }
            return PointParams::Icon::PlayerEliminated;
        }};

ConditionChecker::ConditionCheckResult
EventConditions::PlayerDied::GetResult(const Events::Point &point)
{
    ConditionChecker::ConditionCheckResult result{};

    result.IconColor = PointParams::GetRoleColor(point.ReceiverRole);
    result.Icon = PointParams::Icon::PlayerEliminated;

    const auto receiverRole = Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole);
    const auto giverRole = Events::RoleTypeIdToStringColorFormatted(point.GiverRole);
    if (point.GiverNickname.empty())
    {
        if (LogMessage1PlayerMap.contains(point.DmgType))
        {
            result.AnnounceLogMessage = std::vformat(LogMessage1PlayerMap.at(point.DmgType), std::make_format_args(receiverRole, point.ReceiverNickname));
        }
        else
        {
            std::println("[EventConditions::PlayerDied::GetResult] LogMessage1PlayerMap Not found {}", (int)point.DmgType);
        }
    }
    else
    {
        if (LogMessage2PlayerMap.contains(point.DmgType))
        {
            result.AnnounceLogMessage = std::vformat(LogMessage2PlayerMap.at(point.DmgType), std::make_format_args(receiverRole, point.ReceiverNickname, giverRole, point.GiverNickname));
        }
        else
        {
            std::println("[EventConditions::PlayerDied::GetResult] LogMessage2PlayerMap Not found {}", (int)point.DmgType);
        }
    }

    if (result.AnnounceLogMessage.empty() && !point.Handled)
    {
        result.AnnounceLogMessage = std::format("Player [{}] {} died", Events::RoleTypeIdToStringColorFormatted(point.ReceiverRole), point.ReceiverNickname);
    }

    if (point.Handled)
    {
        result.AnnounceLogMessage.clear();
    }

    for (auto iconFunc : IconFunctions)
    {
        auto icon = iconFunc(point.DmgType);

        if (icon != PointParams::Icon::PlayerEliminated)
        {
            result.Icon = icon;
            break;
        }
    }

    return result;
}