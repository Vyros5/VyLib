#pragma once

#include <stack>
#include <deque>

namespace Vy
{
    /* Adapts a container to provide stack (LIFO data structure) */

    template <typename T, typename TContainer = std::deque<T>> 
    using Stack = std::stack<T, TContainer>;
}
