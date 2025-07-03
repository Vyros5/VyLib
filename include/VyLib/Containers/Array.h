#pragma once

#include <array>

#include "VyLib/Types/CoreTypes.h"

namespace Vy
{
    /* Doubly-linked list */
    /* https://en.cppreference.com/w/cpp/container/array.html */

    template <typename T, SIZE_T N> 
    using Array = std::array<T, N>;
}