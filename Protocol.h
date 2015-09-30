#ifndef Protocol_h__
#define Protocol_h__

#include <cstdint>
#include <cstddef>

#define ASSERT(condition)

namespace BSN
{
    namespace Protocol
    {
#pragma pack(push, 1)
        class __declspec(novtable) Protocol
        {
        public:
            Protocol() { }
            Protocol(std::uint8_t* byteCode, std::size_t byteCodeSize, std::size_t const* codeInfo, std::size_t codeInfoSize);

            std::uint8_t const* TypeInfo(std::uint32_t typeId) const;
            std::uint8_t const* DumpInfo(std::uint32_t typeId) const;
            char const* DumpString(std::uint8_t const* data, std::uint32_t typeId) const;

            std::size_t GetByteCodeSize() const { return _byteCodeSize; }
            std::uint8_t const* GetByteCode() const { return _byteCode; }
            std::size_t GetCodeInfoSize() const { return _codeInfoSize; }
            std::size_t const* GetCodeInfo() const { return _codeInfo; }
            std::size_t GetTypeIdCount() const { return _typeIdCount; }

        private:
            std::size_t _byteCodeSize;
            std::uint8_t* _byteCode;
            std::size_t _codeInfoSize;
            std::size_t const* _codeInfo;
            std::uint32_t _version;
            std::uint32_t dword24;
            std::size_t _typeIdCount;
            std::size_t qword30;
            std::size_t _dumpInfoSize;
            std::uint32_t* _typeInfo;
            std::uint8_t* qword48;
            std::uint32_t* _dumpInfo;
            std::uint8_t* qword58;
        };
#pragma pack(pop)

        template<class T>
        struct TypeIdOf
        {
            static std::uint32_t const Value = T::TypeId;
        };
    }
}

#endif // Protocol_h__
