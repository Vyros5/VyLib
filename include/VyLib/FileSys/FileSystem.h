#pragma once


#include "VyLib/FileSys/File.h"

namespace Vy
{
    /**
     * Platform-Independent FileSystem Interface
     */
    struct FileSystem
    {
        FileSystem()
        {
        }

        virtual ~FileSystem()
        {
        }

        FileSystem(const FileSystem&) = delete;
        FileSystem& operator=(const FileSystem&) = delete;


    };
}