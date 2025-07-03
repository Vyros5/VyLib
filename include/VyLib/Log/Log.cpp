#include "VyLib/Log/Log.h"

#include "VyLib/Containers/Vector.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Vy
{
    SharedPtr<spdlog::logger> Logger::s_ConsoleLogger;
    SharedPtr<spdlog::logger> Logger::s_ClientLogger;

    void Logger::Initialize()
    {
        const auto pattern = fmt::format("%^[%d-%m-%Y %T] [Th: %t] %-7l [{}]: %v [%s:%#] %$", "VyLib");

        spdlog::set_automatic_registration(true);

        Vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(MakeSharedPtr<spdlog::sinks::stdout_color_sink_mt>());
#if VY_CLIENT_LOG_ENABLED
        logSinks.emplace_back(MakeSharedPtr<spdlog::sinks::basic_file_sink_mt>("Logs/VyLib.log", true));
#endif

        for(SIZE_T i = 0; i < logSinks.size(); i++)
        {
            logSinks[i]->set_level(spdlog::level::trace);
            logSinks[i]->set_pattern(pattern);
        }

        s_ConsoleLogger = MakeSharedPtr<spdlog::logger>("ENGINE", logSinks.begin(), logSinks.end());
        s_ClientLogger  = MakeSharedPtr<spdlog::logger>("CLIENT", logSinks.begin(), logSinks.end());
        
        spdlog::set_pattern(pattern);
        s_ConsoleLogger->set_level(spdlog::level::trace);
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    void Logger::Shutdown()
    {
        if (s_ConsoleLogger) 
            s_ConsoleLogger = nullptr;
        
        if (s_ClientLogger)  
            s_ClientLogger  = nullptr;

        spdlog::shutdown();
    }
}


// void Init(StringView applicationName)
// {
//     auto colorSink = MakeSharedPtr<spdlog::sinks::stdout_color_sink_mt>();

//     auto logger = MakeSharedPtr<spdlog::logger>("GLOBAL", colorSink);
//     spdlog::set_default_logger(logger);

//     const auto pattern = fmt::format(
//         "%^[%d-%m-%Y %T] [Th: %t] %-7l [{}]: %v [%s:%#] %$", applicationName
//     );

//     spdlog::set_pattern(pattern);
//     spdlog::set_level(spdlog::level::trace);
// }