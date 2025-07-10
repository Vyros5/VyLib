#pragma once

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Common/Common.h"

namespace Vy
{
    enum class FileMode
    {
        READ,
        WRITE,

    };

    /**
     * Abstraction to access data files
     */
    struct File
    {
        File() 
        {
        }

        virtual ~File() 
        {
        }

        /// @brief Opens the file at path with specified mode.
        virtual void open(cstring path, FileMode mode) = 0;

        /// @brief Closes the file.
        virtual void close() = 0;

        /// @brief Returns whether the file is open.
        virtual bool is_open() = 0;

        /// @brief Returns the size of file in bytes.
        virtual u32 size() = 0;

        /// @brief Returns the number of bytes from the beginning of the file to the cursor position.
        virtual u32 position() = 0;

        /// @brief Returns whether the cursor position is at end of file.
        virtual bool end_of_file() = 0;

        /// @brief Sets the cursor to position.
        virtual void seek(u32 position) = 0;

        /// @brief Sets the cursor position to the end of the file.
        virtual void seek_to_end() = 0;

        /// @brief Sets the cursor position to bytes after current position.
        virtual void skip(u32 bytes) = 0;

        /// @brief Reads size bytes from this into data.
        virtual u32 read(void* data, u32 size) = 0;

        /// @brief Writes size bytes from data to this.
        virtual u32 write(const void* data, u32 size) = 0;

        /// @brief Forces the previous write()s to be transferred to the underlying storage device.
        /// @return 0 if success, -1 otherwise.
        virtual i32 sync() = 0;
    };
}