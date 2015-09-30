#ifndef ByteConverter_h__
#define ByteConverter_h__

#include <algorithm>

namespace ByteConverter
{
    template<std::size_t T>
    inline void convert(char* val)
    {
        std::swap(*val, *(val + T - 1));
        convert<T - 2>(val + 1);
    }

    template<> inline void convert<0>(char*) { }
    template<> inline void convert<1>(char*) { }

    template<typename T>
    inline T ReverseByteOrder(T val)
    {
        convert<sizeof(T)>((char *)&val);
        return val;
    }
}

#endif // ByteConverter_h__
