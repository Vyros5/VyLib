#pragma once

#include <queue>
#include <deque>
#include <vector>
#include <functional>

namespace Vy
{
    /* Adapts a container to provide queue (FIFO data structure) */

    template <typename T, typename TContainer = std::deque<T>>
    using Queue = std::queue<T, TContainer>;


    ///////////////////////////////////////////////////////////////////////////////////////////////

    /* Adapts a container to provide priority queue */
    /* https://en.cppreference.com/w/cpp/container/priority_queue.html */

    template <
        typename T, 
        typename TContainer = std::vector<T>,
        typename TCompare   = std::less<typename TContainer::value_type>
    >
    using PriorityQueue = std::priority_queue<T, TContainer, TCompare>;
    
}
