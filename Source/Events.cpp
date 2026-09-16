#include "Events.hpp"

std::string Events::RoleTypeIdToStringColorFormatted(Events::RoleTypeId role)
{
    Color color = PointParams::GetRoleColor(role);
    return std::format(" ${},{},{},{} {} $255,255,255,255 ", color.r, color.g, color.b, color.a, RoleTypeIdToString(role));
}