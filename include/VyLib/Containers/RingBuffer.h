#pragma once

#include <array>
#include <mutex>
#include <optional>

#include "VyLib/Containers/Array.h"
#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Common/Common.h"

namespace Vy
{
    // https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
    // https://github.com/embeddedartistry/embedded-resources/blob/master/examples/cpp/circular_buffer/circular_buffer.hpp
    
    template<class T, SIZE_T TElemCount>
    class RingBuffer
    {
    public:
        explicit RingBuffer() = default;

        void put(T item) noexcept
        {
            LockGuard<RecursiveMutex> lock(m_Mutex);

            m_Buffer[m_Head] = item;

            if (m_Full)
            {
                m_Tail = (m_Tail + 1) % TElemCount;
            }

            m_Head = (m_Head + 1) % TElemCount;

            m_Full = m_Head == m_Tail;
        }

        Optional<T> get() const noexcept
        {
            LockGuard<RecursiveMutex> lock(m_Mutex);

            if (empty())
            {
                return std::nullopt;
            }

            // Read data and advance the tail (we now have a free space)
            auto val = m_Buffer[m_Tail];
            m_Full = false;
            m_Tail = (m_Tail + 1) % TElemCount;

            return val;
        }

        void reset() noexcept
        {
            LockGuard<RecursiveMutex> lock(m_Mutex);
            m_Head = m_Tail;
            m_Full = false;
        }

        bool empty() const noexcept
        {
            // Can have a race condition in a multi-threaded application
            LockGuard<RecursiveMutex> lock(m_Mutex);

            // if head and tail are equal, we are empty
            return (!m_Full && (m_Head == m_Tail));
        }

        bool full() const noexcept
        {
            // If tail is ahead the head by 1, we are full
            return m_Full;
        }

        SIZE_T capacity() const noexcept
        {
            return TElemCount;
        }

        SIZE_T size() const noexcept
        {
            // A lock is needed in size ot prevent a race condition, because m_Head, m_Tail, and m_Full
            // can be updated between executing lines within this function in a multi-threaded
            // application
            LockGuard<RecursiveMutex> lock(m_Mutex);

            SIZE_T size = TElemCount;

            if(!m_Full)
            {
                if(m_Head >= m_Tail)
                {
                    size = m_Head - m_Tail;
                }
                else
                {
                    size = TElemCount + m_Head - m_Tail;
                }
            }

            return size;
        }

    private:
        mutable Array<T, TElemCount> m_Buffer;
        mutable RecursiveMutex       m_Mutex;
        mutable SIZE_T               m_Head   = 0;
        mutable SIZE_T               m_Tail   = 0;
        mutable bool                 m_Full   = false;
    };
}