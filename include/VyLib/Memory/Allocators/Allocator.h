#pragma once

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Types/StringTypes.h"
#include "VyLib/Prerequisites.h"

// #include "VyLib/Helpers/MemoryOps.h"
#include <cstdlib>

namespace Vy::Memory
{

    template<typename T>
    class Allocator 
    {
    public: 
        
        typedef T                 value_type;
        typedef value_type*       pointer;
        typedef const value_type* const_pointer;
        typedef value_type&       reference;
        typedef const value_type& const_reference;
        typedef SIZE_T            size_type;
        typedef PtrDiff           difference_type;
 
        // convert an allocator<T> to allocator<U>
        template<typename U>
        struct Rebind 
        {
            typedef Allocator<U> other;
        };

        inline explicit Allocator() {}
        inline ~Allocator() {}

        inline explicit Allocator(Allocator const&) {}

        template<typename U>
        inline explicit Allocator(Allocator<U> const&) {}

        // address
        inline pointer       address(reference ref) { return &ref; }
        inline const_pointer address(const_reference ref) { return &ref; }

        // memory allocation
        inline pointer allocate(size_type cnt, typename std::allocator<void>::const_pointer = 0) 
        { 
            return reinterpret_cast<pointer>(::operator new(cnt * sizeof (T))); 
        }

        inline void deallocate(pointer p, size_type) 
        { 
            ::operator delete(p); 
        }

        //    size
        inline size_type max_size() const 
        { 
            return std::numeric_limits<size_type>::max() / sizeof(T);
    }

        //    construction/destruction
        inline void construct(pointer p, const T& t) { new(p) T(t); }
        inline void destroy(pointer p)               { p->~T(); }

        inline bool operator==(Allocator const&)   { return true; }
        inline bool operator!=(Allocator const& a) { return !operator==(a); }
    };


    struct ArenaAllocator;
    
    
    struct ArenaTemp
    {
        ArenaAllocator* pArena         = nullptr;
        SIZE_T          currentOffset  = 0;
        SIZE_T          previousOffset = 0;
    };


    struct ArenaAllocator
    {
        ~ArenaAllocator();

        void Initialize(u64 size);
    };
}