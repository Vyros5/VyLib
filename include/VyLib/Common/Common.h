#pragma once

#include <utility>
#include <variant>
#include <optional>
#include <functional>
#include <mutex>
#include <atomic>

#include "VyLib/Memory/Ptrs.h"

#include "VyLib/Strings/String.h"

namespace Vy
{
    // ============================================================================================

    using Byte  = unsigned char;
    using Bytes = Vector<Byte>;

    // ============================================================================================

    template <typename T, typename U>
    using Pair = std::pair<T, U>;

    template <typename T, typename U>
    std::pair<T, U> MakePair(const T tVal, const U uVal)
    {
        return std::pair<T&, U&>(tVal, uVal);
    }

    // ============================================================================================

    template <typename... T>
    using Variant = std::variant<T...>;

    template< class T >
    using Optional = std::optional<T>;

    // ============================================================================================

    template <typename T> 
    using Delegate = std::function<T>;

    template <typename T> 
    using Function = std::function<T>;

    // ============================================================================================

    using Mutex     = std::mutex;
    using LockGuard = std::lock_guard<std::mutex>;

    template <typename T>
    using Atomic = std::atomic<T>;

    using AtomicFlag = std::atomic_flag;

    template <typename T>
    using Promise = std::promise<T>;
    
    
    // ============================================================================================
}