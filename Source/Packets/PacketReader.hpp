#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

namespace Packet
{
    class Reader
    {
    public:
        Reader(const std::vector<uint8_t> &data);
        std::string ReadDotNetString();
        std::vector<uint8_t> ReadBytes(int size);
        bool HasRemaining(size_t bytes) const;

        template <typename T>
        T Read()
        {
            static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

            if (!HasRemaining(sizeof(T)))
            {
                return T{};
            }

            T result = 0;
            std::memcpy(&result, m_Data->data() + m_Offset, sizeof(T));
            m_Offset += static_cast<int>(sizeof(T));
            return result;
        }

    private:
        int m_Offset = 0;
        std::vector<uint8_t> *m_Data = nullptr;
    };
}
