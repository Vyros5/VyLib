#pragma once

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Types/StringTypes.h"
#include "VyLib/Prerequisites.h"
#include "VyLib/Memory/Ptrs.h"
#include "VyLib/Utils/ClassUtils.h"
#include <fmt/core.h>
#include <fmt/format.h>

#include <spdlog/spdlog.h>

#include <source_location>

namespace Vy
{

    class Logger
    {
        VY_STATIC_CLASS(Logger)

    public:
        static void Initialize();
        static void Shutdown();

        const static SharedPtr<spdlog::logger>& GetConsoleLogger() { return s_ConsoleLogger; }
        const static SharedPtr<spdlog::logger>& GetClientLogger()  { return s_ClientLogger; }

    private:
        static SharedPtr<spdlog::logger> s_ConsoleLogger;
        static SharedPtr<spdlog::logger> s_ClientLogger;
    };
}

#if VY_CLIENT_LOG_ENABLED
    #define VY_TRACE(...)    Vy::Logger::GetClientLogger()->trace(__VA_ARGS__);
    #define VY_INFO(...)     Vy::Logger::GetClientLogger()->info(__VA_ARGS__);
    #define VY_WARN(...)     Vy::Logger::GetClientLogger()->warn(__VA_ARGS__);
    #define VY_ERROR(...)    Vy::Logger::GetClientLogger()->error(__VA_ARGS__);
    #define VY_CRITICAL(...) Vy::Logger::GetClientLogger()->critical(__VA_ARGS__);
#else
    #define VY_TRACE(...)    Vy::Logger::GetConsoleLogger()->trace(__VA_ARGS__);
    #define VY_INFO(...)     Vy::Logger::GetConsoleLogger()->info(__VA_ARGS__);
    #define VY_WARN(...)     Vy::Logger::GetConsoleLogger()->warn(__VA_ARGS__);
    #define VY_ERROR(...)    Vy::Logger::GetConsoleLogger()->error(__VA_ARGS__);
    #define VY_CRITICAL(...) Vy::Logger::GetConsoleLogger()->critical(__VA_ARGS__);
#endif



// namespace Details
// {
//     struct FormatWithLocation 
//     {
//         StringView         format;
//         spdlog::source_loc srcLoc;

//         template <typename String>
//         requires std::constructible_from<StringView, String>
//         FormatWithLocation(const String& str, const std::source_location& location = std::source_location::current()) :
//             format(str),
//             srcLoc(
//                 location.file_name(), static_cast<int>(location.line()),
//                 location.function_name()
//             ) 
//         {
//         }
//     };


//     template <typename... Args>
//     [[noreturn]] constexpr inline void abort(const FormatWithLocation& formatString, Args&&... args) 
//     {
//         fmt::println(fmt::runtime(formatString.fmt), std::forward<Args>(args)...);
//         std::abort();
//     }
// } // namespace Details


// void Init(StringView applicationName);


// template <typename... Args>
// void debug(Details::FormatWithLocation fmt, Args&&... args) 
// {
//     spdlog::default_logger_raw()->log(
//         fmt.srcLoc, 
//         spdlog::level::debug, 
//         fmt::runtime(fmt.format),
//         std::forward<Args>(args)...
//     );
// }

// template <typename... Args>
// void error(Details::FormatWithLocation fmt, Args&&... args) 
// {
//     spdlog::default_logger_raw()->log(
//         fmt.srcLoc, 
//         spdlog::level::err, 
//         fmt::runtime(fmt.format), 
//         std::forward<Args>(args)...
//     );
// }

// template <typename... Args>
// void info(Details::FormatWithLocation fmt, Args&&... args) 
// {
//     spdlog::default_logger_raw()->log(
//         fmt.srcLoc, 
//         spdlog::level::info, 
//         fmt::runtime(fmt.format),
//         std::forward<Args>(args)...
//     );
// }

// template <typename... Args>
// void trace(Details::FormatWithLocation fmt, Args&&... args) 
// {
//     spdlog::default_logger_raw()->log(
//         fmt.srcLoc, 
//         spdlog::level::trace, 
//         fmt::runtime(fmt.format),
//         std::forward<Args>(args)...
//     );
// }

// template <typename... Args>
// void warn(Details::FormatWithLocation fmt, Args&&... args) 
// {
//     spdlog::default_logger_raw()->log(
//         fmt.srcLoc, 
//         spdlog::level::warn, 
//         fmt::runtime(fmt.format),
//         std::forward<Args>(args)...
//     );
// }

// template <typename... Args>
// [[noreturn]] void panic(Details::FormatWithLocation fmt, Args&&... args) 
// {
//     fmt::println("!! PANIC, unexpected path executed: {}:{} - {}", fmt.srcLoc.filename, fmt.srcLoc.line, fmt.srcLoc.funcname);
//     Details::abort(fmt, std::forward<Args>(args)...);
// }

// template <typename... Args>
// void expect(bool condition, Details::FormatWithLocation fmt, Args&&... args) 
// {
//     if (!condition) [[unlikely]] 
//     {
//         fmt::println("!! ASSERTION FAILED: {}:{} - {}", fmt.srcLoc.filename, fmt.srcLoc.line, fmt.srcLoc.funcname);
//         Details::abort(fmt, std::forward<Args>(args)...);
//     }
// }


// namespace Internal
// {
//     template <typename... Args>
//     void debug(Details::FormatWithLocation fmt, Args&&... args) 
//     {
//     #ifdef VY_ENABLE_INTERNAL_LOGGING
//         log::debug(std::move(fmt), std::forward<Args>(args)...);
//     #endif
//     }

//     template <typename... Args>
//     void error(Details::FormatWithLocation fmt, Args&&... args) 
//     {
//     #ifdef VY_ENABLE_INTERNAL_LOGGING
//         log::error(std::move(fmt), std::forward<Args>(args)...);
//     #endif
//     }

//     template <typename... Args>
//     void info(Details::FormatWithLocation fmt, Args&&... args) 
//     {
//     #ifdef VY_ENABLE_INTERNAL_LOGGING
//         log::info(std::move(fmt), std::forward<Args>(args)...);
//     #endif
//     }

//     template <typename... Args>
//     void trace(Details::FormatWithLocation fmt, Args&&... args) 
//     {
//     #ifdef VY_ENABLE_INTERNAL_LOGGING
//         log::trace(std::move(fmt), std::forward<Args>(args)...);
//     #endif
//     }

//     template <typename... Args>
//     void warn(Details::FormatWithLocation fmt, Args&&... args) 
//     {
//     #ifdef VY_ENABLE_INTERNAL_LOGGING
//         log::warn(std::move(fmt), std::forward<Args>(args)...);
//     #endif
//     }
// }