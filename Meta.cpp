#include "Meta.h"
#include "Protocol.h"

std::uint32_t BSN::Protocol::Meta::PeekHeaderEnum(Protocol const* protocol, std::uint32_t typeId)
{
    return *protocol->TypeInfo(typeId) & 0x3F;
}

BSN::Protocol::Meta::Base::Base(Protocol const* protocol, std::uint32_t typeId)
    : _protocol(protocol), _typeId(typeId)
{
    ASSERT(_typeId < _protocol->GetTypeIdCount());

    _typeInfo = _protocol->TypeInfo(_typeId);
    _dumpInfo = _protocol->DumpInfo(_typeId);

    std::size_t const* codeInfo = protocol->GetCodeInfo();
    if (std::size_t offset = codeInfo[_typeId + 1])
        _20 = &codeInfo[offset];
    else
        _20 = nullptr;

    _typeIndex = *_typeInfo;
    ++_typeInfo;
}

bool BSN::Protocol::Meta::Choice::GetFieldTypeId(std::size_t index, std::uint32_t& memberTypeId) const
{
    if (index >= _size)
        return false;

    if (_typeIndex & 0x80)
    {
        std::uint8_t const* v8 = &_typeInfo[4 * index];
        Type::GetTypeId(v8, memberTypeId);
    }
    else
    {
        std::uint8_t const* v5 = &_typeInfo[4 * index] + (_size << (_bounds.dword0 >> 1));
        Type::GetTypeId(v5, memberTypeId);
    }

    return true;
}

bool BSN::Protocol::Meta::Struct::GetMember(std::size_t index, std::size_t& a2, std::uint32_t& memberTypeId) const
{
    if (index >= _size)
        return false;

    if (_20)
        a2 = _20[index + 1];

    if (_typeIndex & 0x80)
    {
        std::uint8_t const* v8 = &_typeInfo[4 * index];
        Type::GetTypeId(v8, memberTypeId);
    }
    else
    {
        std::uint8_t const* v5 = &_typeInfo[4 * index] + (_size << (_bounds.dword0 >> 1));
        Type::GetTypeId(v5, memberTypeId);
    }

    return true;
}
