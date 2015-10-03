#ifndef Type_h__
#define Type_h__

#include <cstdint>
#include <cstddef>
#include <string>

namespace BSN
{
    namespace Protocol
    {
        namespace Type
        {
            struct Bounds
            {
            public:
                static void Get(bool a1, std::uint8_t const*& typeInfo, Bounds& result);

                bool IsUnsigned() const { return dword0 & 1; }
                std::string MinStr() const
                {
                    if (IsUnsigned())
                        return std::to_string(Min);
                    return std::to_string((std::int64_t)Min);
                }
                std::string MaxStr() const
                {
                    if (IsUnsigned())
                        return std::to_string(Max);
                    return std::to_string((std::int64_t)Max);
                }

                std::uint32_t dword0;
                std::uint64_t Bits;
                std::uint64_t Min;
                std::uint64_t Max;
                std::uint8_t byte20;
            };

            struct Int
            {
                static void GetSize(std::uint8_t const*& typeInfo, std::size_t& result);
                static void Get(std::uint32_t typeFlags, std::uint8_t const*& typeInfo, std::size_t& result);
            };

            void GetTypeId(std::uint8_t const*& typeInfo, std::uint32_t& typeId);
        }
    }
}

#endif // Type_h__
