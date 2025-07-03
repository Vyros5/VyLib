#pragma once

#include <bit>
#include <array>
#include <algorithm>

#include "VyLib/Prerequisites.h"

namespace Vy
{
    /**
     * Endianness
     * 
     * https://en.wikipedia.org/wiki/Endianness#Overview
     * https://en.cppreference.com/w/cpp/types/endian.html
     */
    struct Endianness
    {
        template <typename T>
        static VYINLINE void SwapEndian(
            T& val,
            typename std::enable_if<std::is_arithmetic<T>::value, std::nullptr_t>::type = nullptr)
        {
            union U
            {
                T val;
                std::array<std::uint8_t, sizeof(T)> raw;
            } src, dst;

            src.val = val;
            std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
            val = dst.val;
        }

        static VYINLINE bool ShouldSwap()
        {
            return std::endian::native == std::endian::big;
        }
    };
}