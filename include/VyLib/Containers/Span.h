#pragma once

#include <span>

namespace Vy
{
    /* A non-owning view over a contiguous sequence of objects */
    /* https://en.cppreference.com/w/cpp/container/span.html */

    template <typename T> 
    using Span = std::span<T>;
}