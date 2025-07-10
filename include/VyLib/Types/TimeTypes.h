#pragma once

#include <chrono>

namespace Chr = std::chrono;

namespace Time
{
    /* DURATIONS */

    using Years        = std::chrono::years;        // duration type with Period std::ratio<31556952>
    using Months       = std::chrono::months;       // duration type with Period std::ratio<2629746>
    using Weeks        = std::chrono::weeks;        // duration type with Period std::ratio<604800>
    using Days         = std::chrono::days;         // duration type with Period std::ratio<86400>
    using Hours        = std::chrono::hours;        // duration type with Period std::ratio<3600>
    using Minutes      = std::chrono::minutes;      // duration type with Period std::ratio<60>
    using Seconds      = std::chrono::seconds;      // duration type with Period std::ratio<1>
    using MilliSeconds = std::chrono::milliseconds; // duration type with Period std::milli (1000)
    using MicroSeconds = std::chrono::microseconds; // duration type with Period std::micro (1000000)
    using NanoSeconds  = std::chrono::nanoseconds;  // duration type with Period std::nano  (1000000000)


    /* CLOCKS */

    /// @brief Wall clock time from the system-wide realtime clock.
    using SystemClock = std::chrono::system_clock;

    /// @brief Monotonic clock that will never be adjusted.
    using SteadyClock = std::chrono::steady_clock;

    /// @brief Clock with the shortest tick period available.
    using DetailClock = std::chrono::high_resolution_clock;

    /// @brief Clock for Coordinated Universal Time (UTC).
    using UTC_Clock   = std::chrono::utc_clock;

    /* TIME POINTS */

    template <typename TClock, typename TDur = typename TClock::duration>
    using TimePoint = std::chrono::time_point<TClock, TDur>;


}