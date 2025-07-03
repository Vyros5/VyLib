#pragma once

#include <set>
#include <unordered_set>

#include <functional>
#include <memory>

namespace Vy
{
    /* Collection of unique keys, sorted by keys */
    /* https://en.cppreference.com/w/cpp/container/set.html */

    template <
        typename TKey, 
        typename TCompare   = std::less<TKey>, 
        typename TAllocator = std::allocator<TKey>
    >
    using Set = std::set<TKey, TCompare, TAllocator>;


    ///////////////////////////////////////////////////////////////////////////////////////////////

    /* Collection of keys, sorted by keys */
    /* https://en.cppreference.com/w/cpp/container/multiset.html */

    template <
        typename TKey, 
        typename TCompare   = std::less<TKey>, 
        typename TAllocator = std::allocator<TKey>
    >
    using MultiSet = std::multiset<TKey, TCompare, TAllocator>;


    ///////////////////////////////////////////////////////////////////////////////////////////////

    /* Collection of unique keys, hashed by keys */
    /* https://en.cppreference.com/w/cpp/container/unordered_set.html */

    template <
        typename TKey,
        typename THash      = std::hash<TKey>,
        typename TKeyEqual  = std::equal_to<TKey>,
        typename TAllocator = std::allocator<TKey>
    > 
    using HashSet = std::unordered_set<TKey, THash, TKeyEqual, TAllocator>;


    ///////////////////////////////////////////////////////////////////////////////////////////////
    
    /* Collection of keys, hashed by keys */
    /* https://en.cppreference.com/w/cpp/container/unordered_multiset.html */

    template <
        typename TKey, 
        typename THash      = std::hash<TKey>,
        typename TKeyEqual  = std::equal_to<TKey>,
        typename TAllocator = std::allocator<TKey>
    > 
    using HashMultiSet = std::unordered_multiset<TKey, THash, TKeyEqual, TAllocator>;

}