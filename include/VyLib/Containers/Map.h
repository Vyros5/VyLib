#pragma once

#include <map>
#include <unordered_map>

#include <memory>
#include <functional>

namespace Vy
{
    /* Collection of key-value pairs, sorted by keys, keys are unique  */
    /* https://en.cppreference.com/w/cpp/container/map.html */

    template <
        typename TKey, 
        typename T, 
        typename TCompare   = std::less<TKey>, 
        typename TAllocator = std::allocator<std::pair<const TKey, T>>
    > 
    using Map = std::map<TKey, T, TCompare, TAllocator>;


    ///////////////////////////////////////////////////////////////////////////////////////////////

    /* Collection of key-value pairs, sorted by keys  */
    /* https://en.cppreference.com/w/cpp/container/multimap.html */

    template <
        typename TKey, 
        typename T, 
        typename TCompare   = std::less<TKey>, 
        typename TAllocator = std::allocator<std::pair<const TKey, T>>
    > 
    using MultiMap = std::multimap<TKey, T, TCompare, TAllocator>;


    ///////////////////////////////////////////////////////////////////////////////////////////////

    /* Collection of key-value pairs, sorted by keys, keys are unique */
    /* https://en.cppreference.com/w/cpp/container/unordered_map.html */

    template <
        typename TKey, 
        typename T,
        typename THash      = std::hash<TKey>,
        typename TKeyEqual  = std::equal_to<TKey>,
        typename TAllocator = std::allocator<std::pair<const TKey, T>>
    > 
    using HashMap = std::unordered_map<TKey, T, THash, TKeyEqual, TAllocator>;


    ///////////////////////////////////////////////////////////////////////////////////////////////

    /* Collection of key-value pairs, hashed by keys */
    /* https://en.cppreference.com/w/cpp/container/unordered_multimap.html */

    template <
        typename TKey, 
        typename T,
        typename THash      = std::hash<TKey>,
        typename TKeyEqual  = std::equal_to<TKey>,
        typename TAllocator = std::allocator<std::pair<const TKey, T>>
    > 
    using HashMultiMap = std::unordered_multimap<TKey, T, THash, TKeyEqual, TAllocator>;
    
}
