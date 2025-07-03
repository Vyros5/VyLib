#pragma once

#include <forward_list>
#include <list>
#include <memory>

namespace Vy
{
    /* Doubly-linked list */
    /* https://en.cppreference.com/w/cpp/container/list.html */

    template <typename T, typename TAllocator = std::allocator<T>> 
    using List = std::list<T, TAllocator>;


    
    /* Singly-linked list */
    /* https://en.cppreference.com/w/cpp/container/forward_list.html */
    
    template <typename T, typename Allocator = std::allocator<T>> 
    using ForwardList = std::forward_list<T, Allocator>;
}