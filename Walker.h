#ifndef Walker_h__
#define Walker_h__

#include "Meta.h"

namespace BSN
{
    namespace Protocol
    {
        namespace Meta
        {
            class Walker
            {
            public:
                template<class Visitor>
                static std::uint32_t Walk(Visitor& visitor, typename Visitor::Context const& context)
                {
                    Protocol const* protocol = context.GetProtocol();
                    std::uint32_t typeId = context.GetTypeId();
                    switch (PeekHeaderEnum(protocol, typeId))
                    {
                        case 1:
                        {
                            Array arr(protocol, typeId);
                            return visitor.VisitArray(arr, context);
                        }
                        case 2:
                        {
                            AsciiString str(protocol, typeId);
                            return visitor.VisitAsciiString(str, context);
                        }
                        case 3:
                        {
                            BitArray bitArray(protocol, typeId);
                            return visitor.VisitBitArray(bitArray, context);
                        }
                        case 4:
                        {
                            Blob blob(protocol, typeId);
                            return visitor.VisitBlob(blob, context);
                        }
                        case 5:
                        {
                            Bool b(protocol, typeId);
                            return visitor.VisitBool(b, context);
                        }
                        case 6:
                        {
                            Choice choice(protocol, typeId);
                            return visitor.VisitChoice(choice, context);
                        }
                        case 7:
                        {
                            Enum e(protocol, typeId);
                            return visitor.VisitEnum(e, context);
                        }
                        case 8:
                        {
                            FourCC fcc(protocol, typeId);
                            return visitor.VisitFourCC(fcc, context);
                        }
                        case 9:
                        {
                            Int i(protocol, typeId);
                            return visitor.VisitInt(i, context);
                        }
                        case 10:
                        {
                            Null null(protocol, typeId);
                            return visitor.VisitNull(null, context);
                        }
                        case 11:
                        {
                            Optional optional(protocol, typeId);
                            return visitor.VisitOptional(optional, context);
                        }
                        case 12:
                        {
                            Real32 real32(protocol, typeId);
                            return visitor.VisitReal32(real32, context);
                        }
                        case 13:
                        {
                            Real64 real64(protocol, typeId);
                            return visitor.VisitReal64(real64, context);
                        }
                        case 14:
                        {
                            Struct struc(protocol, typeId);
                            return visitor.VisitStruct(struc, context);
                        }
                        case 15:
                        {
                            String str(protocol, typeId);
                            return visitor.VisitString(str, context);
                        }
                        case 16:
                        {
                            User user(protocol, typeId);
                            return visitor.VisitUser(user, context);
                        }
                        default:
                            break;
                    }

                    return 2;
                }
            };
        }
    }
}

#endif // Walker_h__
