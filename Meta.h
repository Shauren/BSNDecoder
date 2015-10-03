#ifndef Meta_h__
#define Meta_h__

#include "Type.h"
#include <vector>
#include <cstdint>
#include <cstddef>

namespace BSN
{
    namespace Protocol
    {
        class Protocol;

        namespace Meta
        {
            std::uint32_t PeekHeaderEnum(Protocol const* protocol, std::uint32_t typeId);

            struct Base
            {
                Base(Protocol const* protocol, std::uint32_t typeId);

                Protocol const* _protocol;
                std::uint32_t _typeId;
                std::uint8_t _typeIndex;
                std::uint8_t const* _typeInfo;
                std::uint8_t const* _dumpInfo;
                std::size_t const* _20;
            };

            struct Array : public Base
            {
                Array(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId),
                    _underlyingType(0)
                {
                    Type::Bounds::Get((_typeIndex & 0x80) != 0, _typeInfo, _bounds);
                    Type::GetTypeId(_typeInfo, _underlyingType);
                }

                Type::Bounds _bounds;
                std::uint32_t _underlyingType;
            };

            struct AsciiString : public Base
            {
                AsciiString(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                    Type::Bounds::Get(false, _typeInfo, _bounds);
                }

                Type::Bounds _bounds;
            };

            struct BitArray : public Base
            {
                BitArray(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                    Type::Bounds::Get(false, _typeInfo, _bounds);
                }

                Type::Bounds _bounds;
            };

            struct Blob : public Base
            {
                Blob(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                    Type::Bounds::Get(false, _typeInfo, _bounds);
                }

                Type::Bounds _bounds;
            };

            struct Bool : public Base
            {
                Bool(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                }
            };

            struct Choice : public Base
            {
                Choice(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId),
                    _size(0)
                {
                    Type::Bounds::Get(false, _typeInfo, _bounds);
                    if (_typeIndex & 0x80)
                    {
                        _size = _bounds.Max - _bounds.Min + 1;
                        _indexes.resize(_size);
                        for (std::size_t i = 0; i < _size; ++i)
                            _indexes[i] = i + _bounds.Min;
                    }
                    else
                    {
                        Type::Int::GetSize(_typeInfo, _size);
                        _indexes.resize(_size);
                        for (std::size_t i = 0; i < _size; ++i)
                        {
                            std::uint8_t const* typeInfo = &_typeInfo[i << (_bounds.dword0 >> 1)];
                            Type::Int::Get(_bounds.dword0, typeInfo, _indexes[i]);
                        }
                    }
                }

                bool GetFieldTypeId(std::size_t index, std::uint32_t& memberTypeId) const;

                Type::Bounds _bounds;
                std::size_t _size;
                std::vector<std::size_t> _indexes;
            };

            struct Enum : public Base
            {
                Enum(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId),
                    _size(0)
                {
                    Type::Bounds::Get(false, _typeInfo, _bounds);
                    if (_typeIndex & 0x80)
                    {
                        _size = _bounds.Max - _bounds.Min + 1;
                        _indexes.resize(_size);
                        for (std::size_t i = 0; i < _size; ++i)
                            _indexes[i] = i + _bounds.Min;
                    }
                    else
                    {
                        Type::Int::GetSize(_typeInfo, _size);
                        _indexes.resize(_size);
                        for (std::size_t i = 0; i < _size; ++i)
                        {
                            std::uint8_t const* typeInfo = &_typeInfo[i << (_bounds.dword0 >> 1)];
                            Type::Int::Get(_bounds.dword0, typeInfo, _indexes[i]);
                        }
                    }
                }

                Type::Bounds _bounds;
                std::size_t _size;
                std::vector<std::size_t> _indexes;
            };

            struct FourCC : public Base
            {
                FourCC(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                }
            };

            struct Int : public Base
            {
                Int(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                    Type::Bounds::Get(false, _typeInfo, _bounds);
                }

                Type::Bounds _bounds;
            };

            struct Null : public Base
            {
                Null(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                }
            };

            struct Optional : public Base
            {
                Optional(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId),
                    _underlyingType(0)
                {
                    Type::GetTypeId(_typeInfo, _underlyingType);
                }

                std::uint32_t _underlyingType;
            };

            struct Real32 : public Base
            {
                Real32(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                }
            };

            struct Real64 : public Base
            {
                Real64(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                }
            };

            struct Struct : public Base
            {
                Struct(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId),
                    _size(0)
                {
                    Type::Bounds::Get(false, _typeInfo, _bounds);
                    if (_typeIndex & 0x80)
                        _size = _bounds.Max - _bounds.Min + 1;
                    else
                        Type::Int::GetSize(_typeInfo, _size);
                }

                bool GetMember(std::size_t index, std::size_t&, std::uint32_t& memberTypeId) const;

                Type::Bounds _bounds;
                std::size_t _size;
            };

            struct String : public Base
            {
                String(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId)
                {
                    Type::Bounds::Get(false, _typeInfo, _characterBounds);
                    _byteBounds = _characterBounds;
                    _byteBounds.Bits += 2;
                    _byteBounds.Max *= 4;
                }

                Type::Bounds _byteBounds;
                Type::Bounds _characterBounds;
            };

            struct User : public Base
            {
                User(Protocol const* protocol, std::uint32_t typeId) : Base(protocol, typeId),
                    _underlyingType(0)
                {
                    Type::GetTypeId(_typeInfo, _underlyingType);
                }

                std::uint32_t _underlyingType;
            };
        };
    }
}

#endif // Meta_h__
