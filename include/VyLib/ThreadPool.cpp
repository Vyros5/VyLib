#include "VyLib/ThreadPool.h"

namespace Vy
{
    namespace
    {
        // Stats
        u32 threadCount                = 0;
        Atomic<u32> workingThreadCount = 0;

        // Threads
        Vector<Thread> threads;

        // Tasks
        Deque<Task> tasks;

        // Sync Objects
        Mutex mutexTasks;
        ConditionVariable conditionVariable;

        bool isStopping = false;
    }


    static void thread_loop()
    {
        while (true)
        {
            // Lock tasks mutex
            std::unique_lock<Mutex> lock(mutexTasks);

            // Check condition on notification
            conditionVariable.wait(lock, [] { return !tasks.empty() || isStopping; });

            // If m_stopping is true, it's time to shut everything down
            if (isStopping && tasks.empty())
                return;

            // Get next task in the queue.
            Task task = tasks.front();

            // Remove it from the queue.
            tasks.pop_front();

            // Unlock the mutex
            lock.unlock();

            // Execute the task.
            workingThreadCount++;
            task();
            workingThreadCount--;
        }
    }


    void ThreadPool::Initialize()
    {
        isStopping = false;

        u32 coreCount = Thread::hardware_concurrency() / 2;  // assume physical cores
        threadCount   = std::min(coreCount * 2, coreCount + 4); // 2x for I/O-bound, cap at coreCount + 4

        for (u32 i = 0; i < threadCount; i++)
        {
            threads.emplace_back(Thread(&thread_loop));
        }

        // SP_LOG_INFO("%d threads have been created", thread_count);
    }


    void ThreadPool::Shutdown()
    {
        Flush(true);

        // Put unique lock on task mutex.
        std::unique_lock<Mutex> lock(mutexTasks);

        // Set termination flag to true.
        isStopping = true;

        // Unlock the mutex
        lock.unlock();

        // Wake up all threads.
        conditionVariable.notify_all();

        // Join all threads.
        for (auto& thread : threads)
        {
            thread.join();
        }

        // Empty worker threads.
        threads.clear();
    }


    Future<void> ThreadPool::AddTask(Task&& task)
    {
        // create a packaged task that will give us a future
        auto packaged_task = make_shared<std::packaged_task<void()>>(std::forward<Task>(task));
        
        // get the future before we move the packaged_task into the lambda
        Future<void> future = packaged_task->get_future();
        
        // lock tasks mutex
        std::unique_lock<Mutex> lock(mutexTasks);
        
        // save the task - wrap the packaged_task in a lambda that will execute it
        tasks.emplace_back([packaged_task]()
        {
            (*packaged_task)();
        });
        
        // unlock the mutex
        lock.unlock();
        
        // wake up a thread
        conditionVariable.notify_one();
        
        // return the future that can be used to wait for task completion
        return future;
    }


    void ThreadPool::ParallelLoop(Function<void(u32 workIndexStart, u32 workIndexEnd)>&& function, const u32 workTotal)
    {
        // SP_ASSERT_MSG(workTotal > 1, "A parallel loop can't have a range of 1 or smaller");

        u32               availableThreads = GetIdleThreadCount();
        u32               workPerThread    = workTotal / availableThreads;
        u32               workRemainder    = workTotal % availableThreads;
        u32               workIndex        = 0;
        Atomic<u32>       workDone         = 0;
        ConditionVariable condVar;
        Mutex             condVarMutex;

        // split work into multiple tasks
        while (workIndex < workTotal)
        {
            u32 workToDo = workPerThread;

            // if the work doesn't divide evenly across threads, add the remainder work to the first thread.
            if (workRemainder != 0)
            {
                workToDo     += workRemainder;
                workRemainder = 0;
            }

            AddTask([&function, &workDone, &condVar, workIndex, workToDo]()
            {
                function(workIndex, workIndex + workToDo);
                workDone += workToDo;

                condVar.notify_one(); // notify that a thread has finished its work
            });

            workIndex += workToDo;
        }

        // wait for threads to finish work
        std::unique_lock<Mutex> lock(condVarMutex);
        condVar.wait(lock, [&]() { return workDone == workTotal; });
    }


    void ThreadPool::Flush(bool removeQueued /*= false*/)
    {
        // clear any queued tasks
        if (removeQueued)
        {
            tasks.clear();
        }

        // wait for any tasks to complete
        while (AreTasksRunning())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }


    u32  ThreadPool::GetThreadCount()        { return threadCount; }
    u32  ThreadPool::GetWorkingThreadCount() { return workingThreadCount; }
    u32  ThreadPool::GetIdleThreadCount()    { return threadCount - workingThreadCount; }
    bool ThreadPool::AreTasksRunning()       { return GetIdleThreadCount() != GetThreadCount(); }
}