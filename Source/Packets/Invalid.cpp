#include "Invalid.hpp"
#include <cstring>

Packet::Invalid::Data Packet::Invalid::GetResult(const std::string& eventName)
{
    Data data = {};
    data.Name = eventName;
    return data;
}
