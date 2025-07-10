#pragma once

#include <utility>
#include <variant>
#include <optional>
#include <functional>
#include <mutex>
#include <future>
#include <shared_mutex>
#include <atomic>

#include "VyLib/Pointers/Ptrs.h"

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

    template<typename T> struct RemoveReference      { using Type = T; };
    template<typename T> struct RemoveReference<T&>  { using Type = T; };
    template<typename T> struct RemoveReference<T&&> { using Type = T; };

    template<typename T>
    using RemoveReferenceT = typename RemoveReference<T>::Type;

    template<typename T> 
    constexpr T&& Forward(RemoveReferenceT <T>& t) noexcept 
    {
        return static_cast<T&&>(t);
    }

    template<typename T> 
    constexpr T&& Forward(RemoveReferenceT <T>&& t) noexcept 
    {
        return static_cast<T&&>(t);
    }

    // ============================================================================================

    /**
     * Mutual exclusion
     * Mutual exclusion algorithms prevent multiple threads from simultaneously accessing shared resources.
     * This prevents data races and provides support for synchronization between threads.
     */

    /// @brief provides basic mutual exclusion facility.
    using Mutex                = std::mutex;

    /// @brief provides mutual exclusion facility which implements locking with a timeout.
    using TimedMutex           = std::timed_mutex;

    /// @brief provides shared mutual exclusion facility.
    using SharedMutex          = std::shared_mutex;

    /// @brief provides shared mutual exclusion facility and implements locking with a timeout.
    using SharedTimedMutex     = std::shared_timed_mutex;

    /// @brief provides mutual exclusion facility which can be locked recursively by the same thread.
    using RecursiveMutex       = std::recursive_mutex;

    /// @brief provides mutual exclusion facility which can be locked recursively by the same thread and implements locking with a timeout.
    using RecursiveTimedMutex  = std::recursive_timed_mutex;

    /**
     * Generic mutex management
     */

    /// @brief implements a strictly scope-based mutex ownership wrapper.
    template <typename M = std::mutex>
    using LockGuard = std::lock_guard<M>;

    template <typename M = std::mutex>
    using ScopedLock = std::scoped_lock<M>;

    template <typename M = std::mutex>
    using UniqueLock = std::unique_lock<M>;

    /**
     * Condition variables
     * 
     * 
     * 
     */

    /// @brief provides a condition variable associated with a std::unique_lock.
    using ConditionVariable = std::condition_variable;

    

    template <typename T>
    using Atomic = std::atomic<T>;

    using AtomicFlag = std::atomic_flag;

    template <typename T>
    using Promise = std::promise<T>;
    
    
    // ============================================================================================
}