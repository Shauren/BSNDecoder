#include "Type.h"

void BSN::Protocol::Type::Bounds::Get(bool a1, std::uint8_t const*& typeInfo, Bounds& result)
{
    const unsigned __int8 *v3; // rax@1
    unsigned int v5; // er8@1
    signed __int64 v6; // r10@2
    unsigned __int8 v7; // cl@2
    signed __int64 v8; // rcx@4
    const unsigned __int8 *v9; // rax@4
    signed __int64 v10; // rcx@5
    signed __int64 v11; // r9@7
    unsigned __int8 v12; // cl@7
    int v13; // er8@7
    signed __int64 v14; // rcx@9
    const unsigned __int8 *v15; // rax@9
    signed __int64 v16; // r10@9
    signed __int64 v17; // rcx@10
    unsigned __int8 v18; // cl@11
    signed __int64 v19; // rcx@13
    signed __int64 v20; // rcx@14

    v3 = typeInfo;
    ++typeInfo;
    v5 = *v3;
    result.dword0 = v5;
    if (a1)
    {
        result.byte20 = 0;
        result.Bits = 0LL;
        v6 = 1LL << (v5 >> 1);
        v7 = 0;
        if (!(v5 & 1))
            v7 = *typeInfo >> 7;
        v8 = (signed __int64)((unsigned __int64)v7 << 63) >> 63;
        result.Min = v8;
        v9 = v3 + 2;
        do
        {
            v10 = v8 << 8;
            result.Min = v10;
            typeInfo = v9;
            v8 = *(v9 - 1) | (unsigned __int64)v10;
            result.Min = v8;
            ++v9;
            --v6;
        } while (v6);
        result.Max = v8;
    }
    else
    {
        result.byte20 = v3[1] >> 7;
        typeInfo = v3 + 2;
        result.Bits = v3[1] & 0x7F;
        v11 = 1LL << (v5 >> 1);
        v12 = 0;
        v13 = v5 & 1;
        if (!v13)
            v12 = v3[2] >> 7;
        v14 = (signed __int64)((unsigned __int64)v12 << 63) >> 63;
        result.Min = v14;
        v15 = v3 + 3;
        v16 = v11;
        do
        {
            v17 = v14 << 8;
            result.Min = v17;
            typeInfo = v15;
            v14 = *(v15 - 1) | (unsigned __int64)v17;
            result.Min = v14;
            ++v15;
            --v16;
        } while (v16);
        v18 = 0;
        if (!v13)
            v18 = *(v15 - 1) >> 7;
        v19 = (signed __int64)((unsigned __int64)v18 << 63) >> 63;
        result.Max = v19;
        do
        {
            v20 = v19 << 8;
            result.Max = v20;
            typeInfo = v15;
            v19 = *(v15 - 1) | (unsigned __int64)v20;
            result.Max = v19;
            ++v15;
            --v11;
        } while (v11);
    }
}

void BSN::Protocol::Type::Int::GetSize(std::uint8_t const*& typeInfo, std::size_t& result)
{
    std::uint8_t const* v4; // rax@3
    std::uint32_t v5; // rcx@3
    std::uint32_t v6; // rcx@4

    //ASSERT(typeInfo[0] & 1); // !IsSigned
    std::uint8_t size = 1 << (typeInfo[0] >> 1);
    //ASSERT(size <= sizeof(std::size_t));

    result = 0;
    v4 = &typeInfo[2];
    v5 = 0;
    do
    {
        v6 = v5 << 8;
        result = v6;
        typeInfo = v4;
        v5 = *(v4 - 1) | v6;
        result = v5;
        ++v4;
        --size;
    } while (size);
}

void BSN::Protocol::Type::Int::Get(std::uint32_t typeFlags, std::uint8_t const*& typeInfo, std::size_t& result)
{
    signed __int64 v3; // r9@1
    unsigned __int8 const *v4; // rcx@1
    unsigned __int8 v5; // r8@1
    signed __int64 v6; // rdi@3
    unsigned __int8 const *v7; // rcx@3
    signed __int64 v8; // rdi@4

    v3 = 1LL << (typeFlags >> 1);
    v4 = typeInfo;
    v5 = 0;
    if (!(typeFlags & 1))
        v5 = *v4 >> 7;

    v6 = (signed __int64)((unsigned __int64)v5 << 63) >> 63;
    v7 = v4 + 1;
    do
    {
        v8 = v6 << 8;
        typeInfo = v7;
        v6 = *(v7 - 1) | (unsigned __int64)v8;
        result = v6;
        ++v7;
        --v3;
    } while (v3);
}

void BSN::Protocol::Type::GetTypeId(std::uint8_t const*& typeInfo, std::uint32_t& typeId)
{
    typeId = (((((typeInfo[0] << 8) | typeInfo[1]) << 8) | typeInfo[2]) << 8) | typeInfo[3];
    typeInfo += 4;
}
