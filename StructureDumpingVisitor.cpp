#include "StructureDumpingVisitor.h"
#include "Walker.h"

std::uint32_t StructureDumpingVisitor::VisitArray(BSN::Protocol::Meta::Array const& t, Context const& ctx)
{
    _result << Pad() << "[" << t._bounds.Min << ',' << t._bounds.Max << "]: {" << std::endl;
    Context userCtx;
    userCtx._protocol = ctx.GetProtocol();
    userCtx._typeId = t._underlyingType;
    std::uint32_t result = RecurseWalk(userCtx);
    _result << Pad() << "}" << std::endl;
    return result;
}

std::uint32_t StructureDumpingVisitor::VisitAsciiString(BSN::Protocol::Meta::AsciiString const& t, Context const& ctx)
{
    _result << Pad() << "AsciiString " << t._protocol->DumpString(t._dumpInfo, 0) << "[" << t._bounds.Min << ',' << t._bounds.Max << "]: {" << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitBitArray(BSN::Protocol::Meta::BitArray const& t, Context const& ctx)
{
    _result << Pad() << "BitArray " << t._protocol->DumpString(t._dumpInfo, 0) << "[" << t._bounds.Min << ',' << t._bounds.Max << "]: {" << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitBlob(BSN::Protocol::Meta::Blob const& t, Context const& ctx)
{
    _result << Pad() << "Blob " << t._protocol->DumpString(t._dumpInfo, 0) << "[" << t._bounds.Min << ',' << t._bounds.Max << "]: {" << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitBool(BSN::Protocol::Meta::Bool const& t, Context const& ctx)
{
    _result << Pad() << "Bool " << t._protocol->DumpString(t._dumpInfo, 0) << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitChoice(BSN::Protocol::Meta::Choice const& t, Context const& ctx)
{
    _result << Pad() << "Choice " << t._protocol->DumpString(t._dumpInfo, 0) << ": {" << std::endl;
    std::uint32_t i = 0;
    std::uint32_t memberTypeId;
    ++_indent;
    while (t.GetFieldTypeId(i, memberTypeId))
    {
        _result << Pad() << t._protocol->DumpString(t._dumpInfo, i + 1) << ": {" << std::endl;
        Context userCtx;
        userCtx._protocol = ctx.GetProtocol();
        userCtx._typeId = memberTypeId;
        std::uint32_t result = RecurseWalk(userCtx);
        ++i;
        _result << Pad() << "}" << std::endl;
    }
    --_indent;
    _result << Pad() << "}" << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitEnum(BSN::Protocol::Meta::Enum const& t, Context const& ctx)
{
    _result << Pad() << "Enum " << t._protocol->DumpString(t._dumpInfo, 0) << ": {" << std::endl;
    std::uint32_t i = 0;
    std::uint32_t memberTypeId;
    ++_indent;
    while (i < t._size)
    {
        _result << Pad() << t._protocol->DumpString(t._dumpInfo, i + 1) << " = " << i << std::endl;
        ++i;
    }
    --_indent;
    _result << Pad() << "}" << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitFourCC(BSN::Protocol::Meta::FourCC const& t, Context const& ctx)
{
    _result << Pad() << "FourCC " << t._protocol->DumpString(t._dumpInfo, 0) << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitInt(BSN::Protocol::Meta::Int const& t, Context const& ctx)
{
    _result << Pad() << "Int " << t._protocol->DumpString(t._dumpInfo, 0) << "[" << t._bounds.Min << ':' << t._bounds.Max << ", bits: " << t._bounds.Bits << "]" << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitNull(BSN::Protocol::Meta::Null const& t, Context const& ctx)
{
    _result << Pad() << "Null " << t._protocol->DumpString(t._dumpInfo, 0) << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitOptional(BSN::Protocol::Meta::Optional const& t, Context const& ctx)
{
    _result << Pad() << "Optional " << t._protocol->DumpString(t._dumpInfo, 0) << ": {" << std::endl;
    Context userCtx;
    userCtx._protocol = ctx.GetProtocol();
    userCtx._typeId = t._underlyingType;
    std::uint32_t result = RecurseWalk(userCtx);
    _result << Pad() << "}" << std::endl;
    return result;
}

std::uint32_t StructureDumpingVisitor::VisitReal32(BSN::Protocol::Meta::Real32 const& t, Context const& ctx)
{
    _result << Pad() << "Real32 " << t._protocol->DumpString(t._dumpInfo, 0) << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitReal64(BSN::Protocol::Meta::Real64 const& t, Context const& ctx)
{
    _result << Pad() << "Real64 " << t._protocol->DumpString(t._dumpInfo, 0) << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitStruct(BSN::Protocol::Meta::Struct const& t, Context const& ctx)
{
    _result << Pad() << t._protocol->DumpString(t._dumpInfo, 0) << ": {" << std::endl;
    std::uint32_t i = 0;
    std::size_t unused;
    std::uint32_t memberTypeId;
    ++_indent;
    while (t.GetMember(i, unused, memberTypeId))
    {
        _result << Pad() << t._protocol->DumpString(t._dumpInfo, i + 1) << ": {" << std::endl;
        Context userCtx;
        userCtx._protocol = ctx.GetProtocol();
        userCtx._typeId = memberTypeId;
        std::uint32_t result = RecurseWalk(userCtx);
        ++i;
        _result << Pad() << "}" << std::endl;
    }
    --_indent;
    _result << Pad() << "}" << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitString(BSN::Protocol::Meta::String const& t, Context const& ctx)
{
    _result << Pad() << "String " << t._protocol->DumpString(t._dumpInfo, 0) << "[" << t._characterBounds.Min << ',' << t._characterBounds.Max << "]: {" << std::endl;
    return 0;
}

std::uint32_t StructureDumpingVisitor::VisitUser(BSN::Protocol::Meta::User const& t, Context const& ctx)
{
    _result << Pad() << t._protocol->DumpString(t._dumpInfo, 0) << ": {" << std::endl;
    Context userCtx;
    userCtx._protocol = ctx.GetProtocol();
    userCtx._typeId = t._underlyingType;
    std::uint32_t result = RecurseWalk(userCtx);
    _result << Pad() << "}" << std::endl;
    return result;
}

std::uint32_t StructureDumpingVisitor::RecurseWalk(Context const& ctx)
{
    ++_indent;
    std::uint32_t result = BSN::Protocol::Meta::Walker::Walk(*this, ctx);
    --_indent;
    return result;
}
