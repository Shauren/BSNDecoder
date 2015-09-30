#ifndef StructureDumpingVisitor_h__
#define StructureDumpingVisitor_h__

#include "Protocol.h"
#include "Meta.h"
#include <sstream>
#include <string>

class StructureDumpingVisitor
{
public:
    struct Context
    {
        BSN::Protocol::Protocol const* GetProtocol() const { return _protocol; }
        std::uint32_t GetTypeId() const { return _typeId; }

        BSN::Protocol::Protocol const* _protocol = nullptr;
        std::uint32_t _typeId = 0;
    };

    std::uint32_t VisitArray(BSN::Protocol::Meta::Array const& t, Context const& ctx);
    std::uint32_t VisitAsciiString(BSN::Protocol::Meta::AsciiString const& t, Context const& ctx);
    std::uint32_t VisitBitArray(BSN::Protocol::Meta::BitArray const& t, Context const& ctx);
    std::uint32_t VisitBlob(BSN::Protocol::Meta::Blob const& t, Context const& ctx);
    std::uint32_t VisitBool(BSN::Protocol::Meta::Bool const& t, Context const& ctx);
    std::uint32_t VisitChoice(BSN::Protocol::Meta::Choice const& t, Context const& ctx);
    std::uint32_t VisitEnum(BSN::Protocol::Meta::Enum const& t, Context const& ctx);
    std::uint32_t VisitFourCC(BSN::Protocol::Meta::FourCC const& t, Context const& ctx);
    std::uint32_t VisitInt(BSN::Protocol::Meta::Int const& t, Context const& ctx);
    std::uint32_t VisitNull(BSN::Protocol::Meta::Null const& t, Context const& ctx);
    std::uint32_t VisitOptional(BSN::Protocol::Meta::Optional const& t, Context const& ctx);
    std::uint32_t VisitReal32(BSN::Protocol::Meta::Real32 const& t, Context const& ctx);
    std::uint32_t VisitReal64(BSN::Protocol::Meta::Real64 const& t, Context const& ctx);
    std::uint32_t VisitStruct(BSN::Protocol::Meta::Struct const& t, Context const& ctx);
    std::uint32_t VisitString(BSN::Protocol::Meta::String const& t, Context const& ctx);
    std::uint32_t VisitUser(BSN::Protocol::Meta::User const& t, Context const& ctx);

    std::string GetResult() const { return _result.str(); }

private:
    std::uint32_t RecurseWalk(Context const& ctx);
    std::string Pad() const { return std::string(_indent, ' '); }

    std::ostringstream _result;
    std::uint32_t _indent = 0;
};

#endif // StructureDumpingVisitor_h__
