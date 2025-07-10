#pragma once

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Types/StringTypes.h"

namespace Vy
{
    struct ByteBuffer 
    {
        u8*    bytes = nullptr;
        SIZE_T size  = 0;

        ByteBuffer() = default;

        ByteBuffer(SIZE_T size) : 
            size(size) 
        {
            bytes = (u8*) malloc(size);
        }

        // Constructor that copies data
        ByteBuffer(const void* data, const SIZE_T size) : 
            size(size) 
        {
            bytes = (u8*) malloc(size);
            if (bytes) 
            {
                memcpy(bytes, data, size);
            } 
            else 
            {
                // Indicate allocation failure
                this->size = 0;
            }
        }

        ~ByteBuffer() 
        {
            release();
        }

        // Copy Constructor (Deep Copy)
        ByteBuffer(const ByteBuffer& other) : size(other.size) 
        {
            if (other.bytes) 
            {
                bytes = (u8*) malloc(size);
                if (bytes) 
                {
                    memcpy(bytes, other.bytes, size);
                } 
                else 
                {
                    size = 0; 
                }
            } 
            else 
            {
                bytes = nullptr;
                size  = 0;
            }
        }

        // Copy Assignment Operator (Rule of Three/Five)
        ByteBuffer& operator=(const ByteBuffer& other) 
        {
            if (this != &other) 
            {
                release();

                size = other.size;
                if (other.bytes) 
                {
                    bytes = (u8*) malloc(size);
                    if (bytes) 
                    {
                        memcpy(bytes, other.bytes, size);
                    }
                    else 
                    {
                        size = 0; 
                    }
                } 
                else 
                {
                    bytes = nullptr;
                    size  = 0;
                }
            }
            return *this;
        }

        operator bool() const 
        {
            return bytes != nullptr && size > 0;
        }

        void release() 
        {
            if (bytes) 
            {
                free(bytes);
                bytes = nullptr;
                size = 0;
            }
        }

        template<typename T>
        T* get() const 
        {
            return (T*) bytes;
        }

        SIZE_T getSize() const 
        {
            return size;
        }
    };
}