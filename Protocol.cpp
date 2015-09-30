#include "Protocol.h"
#include "ByteConverter.h"

BSN::Protocol::Protocol::Protocol(std::uint8_t* byteCode, std::size_t byteCodeSize, std::size_t const* codeInfo, std::size_t codeInfoSize)
{
    signed __int64 dumpInfoOffset; // r9@4
    signed __int64 v11; // r11@7

    _byteCodeSize = byteCodeSize;
    _byteCode = byteCode;
    _codeInfoSize = codeInfoSize;
    _codeInfo = codeInfo;
    ASSERT(byteCodeSize >= 5 * sizeof(std::uint32_t));

    _version = ((((byteCode[1] | (byteCode[0] << 8)) << 8) | byteCode[2]) << 8) | byteCode[3];
    ASSERT(_version == 7);

    dword24 = ((((byteCode[5] | (byteCode[4] << 8)) << 8) | byteCode[6]) << 8) | byteCode[7];

    _typeIdCount = byteCode[11] | (unsigned __int64)((((byteCode[9] | (byteCode[8] << 8)) << 8) | (unsigned int)byteCode[10]) << 8);
    ASSERT(codeInfo[0] == _typeIdCount);

    qword30 = byteCode[15] | (unsigned __int64)((((byteCode[13] | (byteCode[12] << 8)) << 8) | (unsigned int)byteCode[14]) << 8);
    dumpInfoOffset = qword30 + 4 * _typeIdCount + 20;
    _dumpInfoSize  = byteCode[19] | (unsigned __int64)((((byteCode[17] | (byteCode[16] << 8)) << 8) | (unsigned int)byteCode[18]) << 8);
    _typeInfo = (std::uint32_t*)&byteCode[20];
    qword48 = &byteCode[4 * _typeIdCount + 20];
    if (dumpInfoOffset == byteCodeSize)
    {
        _dumpInfoSize = 0LL;
        qword58 = 0LL;
        _dumpInfo = 0LL;
    }
    else
    {
        ASSERT(_dumpInfoSize != 0);

        _dumpInfo = (std::uint32_t*)&byteCode[dumpInfoOffset];
        v11 = dumpInfoOffset + 4 * _typeIdCount;
        qword58 = &byteCode[v11];

        ASSERT(_dumpInfoSize + v11 == byteCodeSize);
    }
}

std::uint8_t const* BSN::Protocol::Protocol::TypeInfo(std::uint32_t typeId) const
{
    ASSERT(typeId < _typeIdCount);
    std::uint32_t offset = ByteConverter::ReverseByteOrder(_typeInfo[typeId]);
    ASSERT(offset < _byteCodeSize);
    return &_byteCode[offset];
}

std::uint8_t const* BSN::Protocol::Protocol::DumpInfo(std::uint32_t typeId) const
{
    ASSERT(typeId < _typeIdCount);
    if (_dumpInfoSize)
    {
        std::uint32_t offset = ByteConverter::ReverseByteOrder(_dumpInfo[typeId]);
        ASSERT(offset < _byteCodeSize);
        if (offset)
            return &_byteCode[offset];
    }

    return nullptr;
}

char const* BSN::Protocol::Protocol::DumpString(std::uint8_t const* data, std::uint32_t typeId) const
{
    if (!_dumpInfoSize || !data)
        return "";

    std::uint32_t offset = ByteConverter::ReverseByteOrder(((std::uint32_t*)data)[typeId]);
    ASSERT(offset < _byteCodeSize);
    if (offset)
        return (char const*)&_byteCode[offset];

    return "";
}
