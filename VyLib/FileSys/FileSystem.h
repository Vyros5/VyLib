#pragma once

#include <fstream>
#include <sstream>

#include "VyLib/Types.h"
#include "VyLib/Defines.h"
// #include "VyLib/

namespace VyLib
{
    bool IsFile(const String& path)
    {
        return std::filesystem::is_regular_file(path);
    }

    bool IsDirectory(const String& path)
    {
        return std::filesystem::is_directory(path);
    }

    StringList ListDirectory(const String& path)
    {
        StringList entries;
        for (auto& entry : std::filesystem::directory_iterator(path))
        {
            entries.emplace_back(entry.path().string());
        }
        
        return entries;
    }


    void WriteFile(const String& path, const String& buffer, bool override = true)
    {
        const auto mode = override ? std::ios::trunc : std::ios::app;
        
        std::ofstream fileStream;
        fileStream.open(path, mode);
        fileStream << buffer;
        fileStream.close();
    }


    void WriteBinaryFile(const String& path, BinaryBufferView buffer, bool override = true)
    {
        const auto mode = override ? std::ios::trunc : std::ios::app;
        
        std::ofstream fileStream;
        fileStream.open(path, mode);
        fileStream.write(reinterpret_cast<cstring>(buffer.data()), buffer.size());
        fileStream.close();
    }


    String ReadFile(const String& path)
    {
        std::ostringstream fileContentStream;
        std::ifstream fstream;

        fstream.open(path);
        fileContentStream << fstream.rdbuf();
        fstream.close();

        return fileContentStream.str();
    }


    BinaryBuffer ReadBinaryFile(const String& path)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        BinaryBuffer buffer(size, 0u);
        file.read(reinterpret_cast<char*>(buffer.data()), size);
        return buffer;
    }

    StringList ReadLines(const String& path);


}