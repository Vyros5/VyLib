#pragma once

#include <condition_variable>
#include <future>

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Common/Common.h"
#include "VyLib/Containers/Deque.h"
#include "VyLib/Utils/ClassUtils.h"

namespace Vy
{
    using Task              = Function<void()>;
    using ConditionVariable = std::condition_variable;
    using Thread            = std::jthread;

    template<typename T>
    using Future  = std::future<T>;
    
    class ThreadPool
    {
        VY_STATIC_CLASS(ThreadPool)

    public:
        
        static void Initialize();
        static void Shutdown();

        // Add a task
        static Future<void> AddTask(Task&& task);

        
        // Spread execution of a given function across all available threads
        static void ParallelLoop(Function<void(u32 workIndexStart, u32 workIndexEnd)>&& function, const u32 workTotal);
        
        // wait for all threads to finish work
        static void Flush(bool removeQueued = false);
        
        static u32  GetThreadCount();
        static u32  GetWorkingThreadCount();
        static u32  GetIdleThreadCount();
        static bool AreTasksRunning();
    };
}